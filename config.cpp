class CfgPatches
{
	class DownedButNotOut
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Scripts"
		};
	};
};

class CfgMods
{
	class DownedButNotOut_Mod
	{
		dir 		= "DownedButNotOut";
		name 		= "";
		author 		= "BuckleBD";
		credits 	= "";
		creditsJSON = "";
		version 	= 1.0.0;
		extra 		= 0;
		type 		= "mod";
		inputs 		= "";
		picture 	= "";
		logo 		= "";
		logoSmall 	= "";
		logoOver 	= "";
		action 		= "";

		dependencies[] = {"Game","World","Mission"};
		
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = {"DownedButNotOut/scripts/3_game"};
			};
			class worldScriptModule
			{
				value = "";
				files[] = {"DownedButNotOut/scripts/4_world"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"DownedButNotOut/scripts/5_mission"};
			};
		};
	};
};