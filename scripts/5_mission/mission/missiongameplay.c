modded class MissionGameplay
{
    protected ref DownedHudWidget m_DownedWidget;

    void MissionGameplay()
    {
        Print("[VignettesDownedButNotOut] MissionGameplay initialized.");
    }

    override void OnInit()
    {
        super.OnInit();
        
        if (!m_DownedWidget)
            m_DownedWidget = new DownedHudWidget();
    }

    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);

        if (m_DownedWidget)
        {
            PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
            
            if (player)
            {
                bool isDowned = player.IsDowned();
                m_DownedWidget.SetVisible(isDowned);
            }
            else
            {
                m_DownedWidget.SetVisible(false);
            }
        }
    }
}