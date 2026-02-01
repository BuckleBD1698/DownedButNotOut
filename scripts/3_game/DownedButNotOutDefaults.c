class DownedButNotOutDefaults
{
	private const static string CONFIG_ROOT     = "$profile:\\Vignettes\\";
	private const static string CONFIG_FILENAME = "DownedButNotOut.json";

	private const static float 	DEFAULT_VERSION = 1.0;
	
	float 	version;
	bool 	enabled;
	float 	downedTime;
	float	reviveTime;
	float	finishTime;

	void DownedButNotOutDefaults()
	{
		version 	= DEFAULT_VERSION;
		enabled 	= true;
		downedTime	= 120.0; // time in seconds before dies while downed
		reviveTime	= 5.0;
		finishTime	= 5.0;
	}

	void Load()
	{
		string filePath = CONFIG_ROOT + CONFIG_FILENAME;

		if (FileExist(filePath))
		{
			Print("[VignettesDownedButNotOut] Loading defaults from " + filePath);
			JsonFileLoader<DownedButNotOutDefaults>.JsonLoadFile(filePath, this);
		}
		else
		{
			Print("[VignettesDownedButNotOut] No settings found, creating defaults at " + filePath);
			Save();
		}
	}

	void Save()
	{
		string filePath = CONFIG_ROOT + CONFIG_FILENAME;

		if (!FileExist(CONFIG_ROOT))
			MakeDirectory(CONFIG_ROOT);

		JsonFileLoader<DownedButNotOutDefaults>.JsonSaveFile(filePath, this);
	}
}

ref DownedButNotOutDefaults g_DownedButNotOutDefaults;

static DownedButNotOutDefaults GetDownedButNotOutDefaults()
{
	if (!g_DownedButNotOutDefaults)
	{
		g_DownedButNotOutDefaults = new DownedButNotOutDefaults();

		if (!GetGame().IsClient())
			g_DownedButNotOutDefaults.Load();
	}
	return g_DownedButNotOutDefaults;
}

static void SetDownedButNotOutDefaults(DownedButNotOutDefaults settings)
{
	g_DownedButNotOutDefaults = settings;
}
