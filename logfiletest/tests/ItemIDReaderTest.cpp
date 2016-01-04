#include "../parser/ItemIDFileReader.h"
#include "gtest/gtest.h"

class ItemIDReaderTest: public testing::Test{
protected:
	ItemIDFileReader itemFile;//("file.txt")	;
	ItemIDReader& reader;;
	ItemIDReaderTest(): itemFile("file.txt"), reader(itemFile){	
		
		cout << "Loading item names" << endl;	
	}		
};

TEST_F(ItemIDReaderTest, readSuccess){
	EXPECT_TRUE(itemFile.isItemIDFileSuccessfullyRead());
}

TEST(ItemIDReaderNegative, readFailure){
	ItemIDFileReader failReader("lsdklsfksldfj");
	EXPECT_FALSE(failReader.isItemIDFileSuccessfullyRead());
}

TEST_F(ItemIDReaderTest, read1){
	//ItemIDReader reader("file.txt");
	cout << "Retrieving item name" << endl;	
	string name = reader.getItemName(101300458);
	cout << "Item name retrieved: " << name << endl;	
	EXPECT_EQ("Noble Dark Dragon King's Polearm", name);

	//EXPECT_EQ(101300458, reader.getItemID("Noble Dark Dragon King's Polearm"));
}

TEST_F(ItemIDReaderTest, read2){
	//ItemIDReader reader("file.txt");
	cout << "Retrieving item name" << endl;	
	string name = reader.getItemName(100000001);
	cout << "Item name retrieved: " << name << endl;	
	EXPECT_EQ("Circulus' Sword", name);

	//EXPECT_EQ(110000001, reader.getItemID("Costume Jacket 1"));
}

TEST_F(ItemIDReaderTest, read3){
	//ItemIDReader reader("file.txt");
	cout << "Retrieving item name" << endl;	
	string name = reader.getItemName(190100133);	
	cout << "Item name retrieved: " << name << endl;	
	EXPECT_EQ("Snowkissed Aetherboard (30 days)", name);
	//EXPECT_EQ(190070016, reader.getItemID("Sidekick Yume Summoning Lamp (30 Days)"));

}

TEST_F(ItemIDReaderTest, readNotExist1){
	//ItemIDReader reader("file.txt");
	cout << "Retrieving item name" << endl;	
	string name = reader.getItemName(123);	
	cout << "Item name retrieved: " << name << endl;	
	EXPECT_EQ("123", name);
	

}

TEST_F(ItemIDReaderTest, readRaw1){
	cout << "Retrieving item name" << endl;	
	string name = reader.getItemName("[item:141000001;ver5;;;;;;]");
	cout << "Item name retrieved: " << name << endl;	
	EXPECT_EQ("Stigma Shard", name);
}

TEST_F(ItemIDReaderTest, readRawNotExist1){
	cout << "Retrieving item name" << endl;	
	string name = reader.getItemName("[item:66666;ver5;;;;;;]");
	cout << "Item name retrieved: " << name << endl;	
	EXPECT_EQ("66666", name);
}

int main(int argc, char** argv){
	testing::InitGoogleTest(&argc, argv); 
	RUN_ALL_TESTS();
	getchar();
	return 0;
}