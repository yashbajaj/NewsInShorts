#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <map>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <cstdlib>
#include <fstream>

using namespace std;

int main()
{

	string news_id,user_id;
	int count;

	vector<string  >  news_mapper;
	vector<string > user_mapper;
	vector<string>::iterator it;	

	ifstream myfile("bipartite_graph.csv");
	string str;

	while(getline(myfile,str))
	{
		
		vector<string> tokens;
		istringstream iss(str);

		copy(istream_iterator<string>(iss),
			istream_iterator<string>(),
			back_inserter(tokens));
		if(tokens.size() != 3 ) continue;
		news_id = tokens[0];
		user_id = tokens[1];
		it = find( news_mapper.begin(), news_mapper.end(), news_id);
		if(it ==  news_mapper.end())
		 news_mapper.push_back( news_id);
		it = find(user_mapper.begin(),user_mapper.end(),user_id);
		if(it == user_mapper.end())
		user_mapper.push_back(user_id);


	}
	cout << "users  " << user_mapper.size() << endl;
	cout << " newss  " <<  news_mapper.size() << endl;

	
	ifstream myfiles("bipartite_graph.csv");


	int ** Adjacency_matrix = (int**)malloc(user_mapper.size() * sizeof(int*));
	for(int i =0 ;i< user_mapper.size();i++)
	{
		Adjacency_matrix[i] = (int*)malloc( news_mapper.size() * sizeof(int));
	}
	int x,y;



	for(int i=0;i<user_mapper.size();i++)
	{
		for(int j=0;j< news_mapper.size();j++)
		{
			Adjacency_matrix[i][j] = 0;
		}
	}
	while(getline(myfiles,str))
	{
		vector<string> tokens;
		istringstream iss(str);

		copy(istream_iterator<string>(iss),
			istream_iterator<string>(),
			back_inserter(tokens));
		if(tokens.size() != 3 ) continue;
		news_id = tokens[0];
		user_id = tokens[1];
		
		x = distance(user_mapper.begin(),find(user_mapper.begin(),user_mapper.end(),user_id));
		y = distance( news_mapper.begin(),find( news_mapper.begin(), news_mapper.end(), news_id));
		Adjacency_matrix[x][y] = 1;

	}

	cout << "Made the adjacency matrix " << endl;

	int **  news_matrix  = (int**)malloc( news_mapper.size()*sizeof(int*));
	for(int i=0;i< news_mapper.size();i++)
	{
		 news_matrix[i] = (int*)malloc( news_mapper.size()*sizeof(int));
	}

	for(int i=0;i< news_mapper.size();i++)
	{
		for(int j=0;j< news_mapper.size();j++)
		{
			 news_matrix[i][j] = 0;
			
			if(i != j) {
			for(int k=0;k<user_mapper.size();k++)
			{
				if(Adjacency_matrix[k][i] > 0 && Adjacency_matrix[k][j] > 0)
				{
					 news_matrix[i][j]++;
				}
			}
		}
		//	cout <<  news_matrix[i][j] << " ";

		}
		//cout << endl;
	}

	cout << "Filled the  news  news matrix " << endl;

	FILE* fp = (FILE*) fopen("CoNewsEdgeList.csv","w");


	for(int i=0;i< news_mapper.size();i++)
	{
		for(int j=0;j< news_mapper.size();j++)
		{
			
			if(news_matrix[i][j] > 0)
			{
				fprintf(fp,"%d %d\n",i,j);
			}

		}

	}

	fclose(fp);

	FILE* op = (FILE*) fopen("NewsMapping.csv","w");
	for(int i=0;i<news_mapper.size();i++)
	{
		fprintf(op,"%d %s\n",i,news_mapper[i].c_str());
	}
	
	return 0;
}