#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

/*These are the thresholds for time to extract out relevant articles and remove outliers where time consumed on article is way too high.
Also the articles which are semi-read are not considered as of now
*/

//6711 faulty data points with ,, together 
//Changed , delimiter to space to avoid the hassle 

#define LOWER_THRESHOLD 4
#define UPPER_THRESHOLD 12

int main()
{
FILE* fp = fopen("test_data.csv","r");
FILE* out = fopen("bipartite_graph.csv","w");
string userId,newsId;
int interval;
printf("Filtering the intervals based on thresholds\n");
int flag = 0;
fprintf(out,"userId,newsId\n");
ifstream myfile("test_data.csv");
string str;

int count = 0;
while(getline(myfile,str))
{
flag = 0;
istringstream iss(str);
vector<string> tokens;
copy(istream_iterator<string>(iss),
			istream_iterator<string>(),
			back_inserter(tokens));
if(tokens.size() != 5) continue;

userId = tokens[1];
newsId = tokens[2];
interval = atof(tokens[4].c_str());
 if( interval > LOWER_THRESHOLD && interval < UPPER_THRESHOLD) flag = 1;

 if(flag == 1)
 {
 fprintf(out,"%s,%s,1\n",newsId.c_str(),userId.c_str());
 }

}

}