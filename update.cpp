

static void update() 
{
	for (GameObject* unit : units)
	{
		switch (unit -> returnAction())
		{
		case idling:
			break;
		case moving:
			(unit->moveEntity());
			break;
			;
		default:
			break;
		}
	}
}