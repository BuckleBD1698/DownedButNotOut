class ActionFinishOffCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		float time = 5.0;

		if (GetDownedButNotOutDefaults())
			time = GetDownedButNotOutDefaults().finishTime;

		m_ActionData.m_ActionComponent = new CAContinuousTime(time);
	}
}

class ActionFinishOff : ActionContinuousBase
{
	void ActionFinishOff()
	{
		m_CallbackClass = ActionFinishOffCB;
		// Use a generic interaction animation, or something aggressive if available
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT; 
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
	}

	override void CreateConditionComponents()  
	{	
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTMan(UAMaxDistances.DEFAULT);
	}

	override string GetText()
	{
		return "Finish Off";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		PlayerBase targetPlayer = PlayerBase.Cast(target.GetObject());
		if (!targetPlayer) return false;

		// Can only finish off downed players
		return targetPlayer.IsDowned();
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		PlayerBase targetPlayer = PlayerBase.Cast(action_data.m_Target.GetObject());
		if (targetPlayer)
		{
			// Instant kill
			targetPlayer.SetHealth("", "", 0.0);
		}
	}
}