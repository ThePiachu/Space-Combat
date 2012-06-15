#include "pilots.h"
bool comparepilotpointerspairf(const pair<pilot*, bool>& One, const pair<pilot*, bool>& Two)
{
	return One.first->score>Two.first->score;
}
