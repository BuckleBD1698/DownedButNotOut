class DownedHudWidget
{
    protected Widget m_RootWidget;

    void DownedHudWidget()
    {
        string layoutPath = "DownedButNotOut/gui/layouts/DownedHud.layout";
        
        m_RootWidget = GetGame().GetWorkspace().CreateWidgets(layoutPath);
        
        if (m_RootWidget)
        {
            m_RootWidget.Show(false);
        }
    }

    void ~DownedHudWidget()
    {
        if (m_RootWidget)
        {
            m_RootWidget.Unlink();
        }
    }

    void SetVisible(bool show)
    {
        if (m_RootWidget)
        {
            if (m_RootWidget.IsVisible() != show)
            {
                m_RootWidget.Show(show);
            }
        }
    }
}