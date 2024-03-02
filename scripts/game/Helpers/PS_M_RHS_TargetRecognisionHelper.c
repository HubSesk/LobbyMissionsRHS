modded class RHS_TargetRecognisionHelper
{	
	static override void GetValideTargets(int cameraIndex, int screenWidth, int screenHeight, vector transform[4], IEntity fromEntity, notnull out array<ref RHS_TargetRecognisionResult> outTargets)
	{
		
	}
	
	static override bool CheckVisibility(vector from, IEntity target, IEntity fromEntity, array<vector> positions)
	{
		return false;
	}
	
	static override bool CheckVisibility(vector from, IEntity target, IEntity fromEntity)
	{
		return false;
	}
	
	static override bool CheckVisibility(vector from, vector to, IEntity target, IEntity fromEntity)
	{
		return false;
	}
}