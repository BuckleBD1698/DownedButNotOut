class ActionReviveCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		float time = 5.0;
		
		if (GetDownedButNotOutDefaults())
			time = GetDownedButNotOutDefaults().reviveTime;

		m_ActionData.m_ActionComponent = new CAContinuousTime(time);
	}
}

class ActionRevive : ActionContinuousBase
{
	void ActionRevive()
	{
		m_CallbackClass = ActionReviveCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_CPR; // Use CPR animation
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
	}

	override void CreateConditionComponents()  
	{	
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTMan(UAMaxDistances.DEFAULT);
	}

	override string GetText()
	{
		return "Revive";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		PlayerBase targetPlayer = PlayerBase.Cast(target.GetObject());
		if (!targetPlayer) return false;

		return targetPlayer.IsDowned();
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		PlayerBase targetPlayer = PlayerBase.Cast(action_data.m_Target.GetObject());
		if (targetPlayer)
		{
			targetPlayer.Revive();
		}
	}
}