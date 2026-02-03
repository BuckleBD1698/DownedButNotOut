modded class PlayerBase
{
	protected bool 		m_IsDowned;
	protected float 	m_DownedTimer;
	static const int 	RPC_DOWNED_MESSAGE = 492381;
	
	void PlayerBase()
	{
		RegisterNetSyncVariableBool("m_IsDowned");
		m_IsDowned 		= false;
		m_DownedTimer 	= 0;
	}

	bool IsDowned()
	{
		return m_IsDowned;
	}

	void SetDowned(bool state, bool resetTimer = true)
	{
		m_IsDowned = state;
		SetSynchDirty();
		
		if (m_IsDowned)
		{			
			// only reset the timer if this is a fresh event (not loading from DB)
			if (resetTimer)
			{
				m_DownedTimer = GetDownedButNotOutDefaults().downedTime;

				if (m_DownedTimer == -1)
					m_DownedTimer = 60.0;			
			}
			
			if (GetGame().IsServer() && GetIdentity())
			{
				Param1<float> p = new Param1<float>(m_DownedTimer);
				GetGame().RPCSingleParam(this, RPC_DOWNED_MESSAGE, p, true, GetIdentity());
				GetGame().GetSoundScene().SetSoundVolume(0.25,1);
			}
			
			// force stance into movement to trigger the force prone
			// TODO: find a better way to handle this, this is ass
			StartCommand_Move();
			HumanCommandMove cm = GetCommand_Move();
			if (cm)
			{
				cm.ForceStance(DayZPlayerConstants.STANCEIDX_PRONE);
			}
		}
	}

	void Revive()
	{
		SetDowned(false);
		
		// give a little health bump on revive - MAYBE REMOVE THIS
		SetHealth("", "", 25.0);
		
		// uncon prevention for testing
		//SetHealth("", "Shock", 100.0);
	}
	
	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);
		
		ctx.Write(m_IsDowned);
		ctx.Write(m_DownedTimer);
	}

	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		if (!super.OnStoreLoad(ctx, version))
			return false;

		if (!ctx.Read(m_IsDowned))
			m_IsDowned = false;
			
		if (!ctx.Read(m_DownedTimer))
			m_DownedTimer = 0;
			
		return true;
	}
	
	override void AfterStoreLoad()
	{
		super.AfterStoreLoad();

		if (m_IsDowned)
			SetDowned(true, false); 

	}

	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();

		if (IsControlledPlayer())
		{
			if (m_IsDowned)
			{
				HumanCommandMove cm = GetCommand_Move();

				if (cm)
					cm.ForceStance(DayZPlayerConstants.STANCEIDX_PRONE);
			}
			else
				GetGame().GetSoundScene().SetSoundVolume(1,1);
		}
	}

	override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
	{
		super.OnRPC(sender, rpc_type, ctx);

		if (rpc_type == RPC_DOWNED_MESSAGE)
		{
			Param1<float> p = new Param1<float>(0);
			if (!ctx.Read(p)) return;

			float time = p.param1;
			string msg = "You have been DOWNED! You have " + time.ToString() + " seconds to be rescued.";
			MessageImportant(msg);
		}
	}

	override bool EEOnDamageCalculated(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		if (!IsAlive())
			return super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);

		string victimInfo = "Unknown";

		if (GetIdentity())
			victimInfo = GetIdentity().GetName() + " (SteamID:" + GetIdentity().GetPlainId() + ")";

		string attackerInfo = "Environment/Unknown";

		if (source)
		{
			attackerInfo = source.GetType();
			PlayerBase attackerPlayer = PlayerBase.Cast(source);

			if (attackerPlayer && attackerPlayer.GetIdentity())
				attackerInfo = attackerPlayer.GetIdentity().GetName() + " (SteamID:" + attackerPlayer.GetIdentity().GetPlainId() + ")";
		}

		if (source == this)
			return super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);

		if (m_IsDowned)
		{
			float currentHealth = GetHealth("", "Health");
			float incomingDamage = damageResult.GetDamage("", "Health");

			if (currentHealth - incomingDamage <= 0)
				Print("[VignettesDownedButNotOut] KILL CONFIRMED: " + victimInfo + " was finished off by " + attackerInfo);

			return super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
		}

		float hp = GetHealth("", "Health");
		float dmg = damageResult.GetDamage("", "Health");

		if (hp - dmg <= 0)
		{
			Print("[VignettesDownedButNotOut] DOWNED STATE TRIGGERED: " + victimInfo + " was downed by " + attackerInfo);

			// downed state trigger, reset timer = true
			SetDowned(true, true);
			
			SetHealth("", "Health", 5.0);

			if (GetHealth("", "Blood") > 3001.0)
				SetHealth("", "Blood", 3001.0);
			
			// uncon prevention for testing
			//SetHealth("", "Shock", 100.0);

			return false;
		}

		return super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
	}

	override void OnScheduledTick(float deltaTime)
	{
		super.OnScheduledTick(deltaTime);
		
		if (GetGame().IsServer() && m_IsDowned)
		{
			m_DownedTimer -= deltaTime;
			
			if (m_DownedTimer <= 0)
			{
				string victimInfo = "Unknown";

				if (GetIdentity())
				{
					victimInfo = GetIdentity().GetName() + " (SteamID:" + GetIdentity().GetPlainId() + ")";
				}

				Print("[VignettesDownedButNotOut] TIMER EXPIRED: " + victimInfo);
				
				GetGame().GetSoundScene().SetSoundVolume(1,1);
				SetHealth("", "", 0.0); // womp womp
			}
			else
			{
				// STAY DOWN
				// TODO: figure out why player can stand back up and stay up sometimes - MAYBE RESOLVED?
				HumanMovementState hms = new HumanMovementState();
				GetMovementState(hms);
				if (hms.m_iStanceIdx != DayZPlayerConstants.STANCEIDX_PRONE)
				{
					HumanCommandMove cm = GetCommand_Move();
					if (cm)
					{
						cm.ForceStance(DayZPlayerConstants.STANCEIDX_PRONE);
					}
				}
			}
		}
	}

	override bool CanJump()
	{
		if (m_IsDowned) return false;
		return super.CanJump();
	}

	override bool CanSprint()
	{
		if (m_IsDowned) return false;
		return super.CanSprint();
	}

	override bool CanChangeStance(int previousStance, int newStance)
	{
		if (m_IsDowned)
		{
			if (newStance == DayZPlayerConstants.STANCEIDX_PRONE)
				return true;
				
			return false;
		}
		
		return super.CanChangeStance(previousStance, newStance);
	}
}