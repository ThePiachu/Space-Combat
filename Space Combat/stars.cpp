#include "stars.h"

bool comparex(const star* one, const star* two)
{
	return one->position.x<two->position.x;
}
bool comparey(const star* one, const star* two)
{
	return one->position.y<two->position.y;
}
bool comparez(const star* one, const star* two)
{
	return one->position.z<two->position.z;
}
