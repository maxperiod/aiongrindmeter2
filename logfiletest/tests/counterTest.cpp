#include "../model/Counter.h"
#include "gtest/gtest.h"

TEST(counter, insert1){
	Counter<string> itamz;

	map<string, CounterEntry>::iterator tada;	
	map<string, CounterEntry>::iterator last;

	itamz.add("Working");
	EXPECT_EQ(1, itamz.getTotalCount());
	
	tada = itamz.begin();	
	EXPECT_EQ("Working", tada->first);
	EXPECT_EQ(1, tada->second.numGained);
	EXPECT_EQ(1, tada->second.numPackets);
	tada ++;
	EXPECT_EQ(tada, itamz.end());

	itamz.add("Sleeping");
	itamz.add("Working");
	itamz.add("QQing", 3);
	EXPECT_EQ(6, itamz.getTotalCount());
	
	last = itamz.getLastUpdated();
	EXPECT_EQ("QQing", last->first);
	EXPECT_EQ(3, last->second.numGained);
	EXPECT_EQ(1, last->second.numPackets);
	
	tada = itamz.begin();
	EXPECT_EQ("QQing", tada->first);
	EXPECT_EQ(3, tada->second.numGained);
	EXPECT_EQ(1, tada->second.numPackets);
	tada ++;
	EXPECT_EQ("Sleeping", tada->first);
	EXPECT_EQ(1, tada->second.numGained);
	EXPECT_EQ(1, tada->second.numPackets);
	tada ++;		
	EXPECT_EQ("Working", tada->first);
	EXPECT_EQ(2, tada->second.numGained);
	EXPECT_EQ(2, tada->second.numPackets);
	tada ++; 
	EXPECT_EQ(tada, itamz.end());

	//EXPECT_EQ(itamz.getLastUpdated().
	
	itamz.add("Sleeping", 3);
	EXPECT_EQ(9, itamz.getTotalCount());	

	tada = itamz.begin();
	tada ++;
	EXPECT_EQ("Sleeping", tada->first);	
	EXPECT_EQ(4, tada->second.numGained);
	EXPECT_EQ(2, tada->second.numPackets);
	
	last = itamz.getLastUpdated();
	EXPECT_EQ("Sleeping", last->first);
	EXPECT_EQ(4, last->second.numGained);
	EXPECT_EQ(2, last->second.numPackets);
	

	
	// Undo last counter addition
	itamz.erase("Sleeping");
	//itamz.eraseLast();
	EXPECT_EQ(5, itamz.getTotalCount());
	tada = itamz.begin();

	EXPECT_EQ("QQing", tada->first);
	EXPECT_EQ(3, tada->second.numGained);
	EXPECT_EQ(1, tada->second.numPackets);
	tada ++;
	EXPECT_EQ("Working", tada->first);
	EXPECT_EQ(2, tada->second.numGained);
	EXPECT_EQ(2, tada->second.numPackets);
	tada ++;		
	EXPECT_EQ(tada, itamz.end());


	last = itamz.getLastUpdated();
	EXPECT_EQ("QQing", last->first);
	EXPECT_EQ(3, last->second.numGained);
	EXPECT_EQ(1, last->second.numPackets);		

	// Single undo only!
	/*
	itamz.eraseLast();
	EXPECT_EQ(5, itamz.getTotalCount());
	tada = itamz.begin();

	EXPECT_EQ("QQing", tada->first);
	EXPECT_EQ(3, tada->second.numGained);
	EXPECT_EQ(1, tada->second.numPackets);
	tada ++;
	EXPECT_EQ("Working", tada->first);
	EXPECT_EQ(2, tada->second.numGained);
	EXPECT_EQ(2, tada->second.numPackets);
	tada ++;		
	EXPECT_EQ(tada, itamz.end());


	last = itamz.getLastUpdated();
	EXPECT_EQ("QQing", last->first);
	EXPECT_EQ(3, last->second.numGained);
	EXPECT_EQ(1, last->second.numPackets);		
	*/
}


TEST(counter, tests2){
	Counter<string> itamz;
	map<string, CounterEntry>::iterator tada;	
	map<string, CounterEntry>::iterator last;

	itamz.add("10016", 471);
	itamz.add("11648", 2);
	itamz.add("10115");
	itamz.add("10115");
	itamz.add("11111", 11);
}

TEST(counter, delete){
	Counter<int> itamz;

	itamz.add(1);
	itamz.add(3, 2);
	itamz.add(6, 3);
	itamz.add(10, 4);

	EXPECT_EQ(10, itamz.getTotalCount());

	EXPECT_EQ(1, itamz.get(1).numGained);
	EXPECT_EQ(2, itamz.get(3).numGained);
	EXPECT_EQ(3, itamz.get(6).numGained);
	EXPECT_EQ(4, itamz.get(10).numGained);

	EXPECT_EQ(10, itamz.getLastUpdated()->first);
	EXPECT_EQ(4, itamz.getLastUpdated()->second.numGained);

	itamz.eraseAll();

	EXPECT_EQ(0, itamz.getTotalCount());

	itamz.add(2, 5);
	itamz.add(4, 25);

	EXPECT_EQ(4, itamz.getLastUpdated()->first);
	EXPECT_EQ(25, itamz.getLastUpdated()->second.numGained);
	
	
	EXPECT_EQ(5, itamz.get(2).numGained);

	EXPECT_EQ(30, itamz.getTotalCount());
	
	map<int, CounterEntry>::iterator tada = itamz.begin();
	EXPECT_EQ(2, tada->first);
	tada ++;
	EXPECT_EQ(4, tada->first);
}