#include "grid.h"

	void grid::preparegrid(const int& SizeInEachDirection, const point& Center)
	{
		point tmppoint;
		vector<map<point, gridelement, pointcompare>::iterator> its;//list of new inserted elements
		pair<map<point, gridelement, pointcompare>::iterator,bool> tmppair;
		map<point, gridelement, pointcompare>::iterator it;//iterator
		for (int i=-SizeInEachDirection;i<=SizeInEachDirection;i++)
		{
			for (int j=-SizeInEachDirection;j<=SizeInEachDirection;j++)
			{
				for (int k=-SizeInEachDirection;k<=SizeInEachDirection;k++)
				{
					//new point index
					tmppoint(Center.//based on the center
							movebyvector(basicvector(//moved by a vector
								i*2.0*sidelength, j*2.0*sidelength, k*2.0*sidelength))
									.approx(sidelength*2.0));//and approximated to grid dimentions
						tmppair=//tries inserting a new grid element into the grid
								gridmap.insert(
								pair<point, gridelement>
									(tmppoint,
									gridelement(tmppoint,
											sidelength)));
						if (tmppair.second)
						{//if true, means it is a new element
							its.push_back(tmppair.first);
						}//otherwise there already is an element like that
				}
			}
		}

		//setting up connections between grid elements
		vector<point> missingneighbours;
		for (unsigned int i=0;i<its.size();i++)
		{
			missingneighbours=(*(its.at(i))).second.givemissingneigbours();
			for (unsigned j=0;j<missingneighbours.size();j++)
			{
				it=gridmap.find(missingneighbours.at(j));
				if (it!=gridmap.end())
				{
					(*(its.at(i))).second.addneighbour(it->second);
					it->second.addneighbour((*(its.at(i))).second);
				}
			}
		}

		//for possible use with metagrid:
		//if(metagrid!=NULL)metagrid->preparegrid(SizeInEachDirection, Center);
	}
