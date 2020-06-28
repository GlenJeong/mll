// Program.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

// The test function list
void test_knn(string, string);
void test_naivebayes(string, string);

int _tmain(int argc, _TCHAR* argv[])
{
// 	test_knn("..\\..\\dataset\\knn\\datingTestSet.txt", "..\\..\\dataset\\knn\\datingTestSet2.txt");
	test_naivebayes("..\\..\\dataset\\bys\\iris_train.txt", "..\\..\\dataset\\bys\\iris_test.txt");

	return 0;
}

// The K-Nearest Neighborhood Classifier
void test_knn(string trainPath, string testPath)
{
	// Load the dataset
	mlldataset trainset(trainPath, "\t", LABEL_REAR);
	mlldataset testset(testPath, "\t", LABEL_REAR);

	// Set a train condition
	const int K = 10;
	const measure& meas = correlation();

	// Train the dataset
	KNN knn(K, meas);
	knn.train(trainset);
	knn.save("..\\knn_result.ini");
// 	knn.open("..\\knn_result.ini");

	// Get a response on the train dataset
	int trainMissed = 0;
	for (int i = 0; i < trainset[0].rows; i++)
	{
		double response = knn.predict(trainset[0].submat(i));
		if (response != trainset[1][i])
		{
			trainMissed++;
		}
	}

	// Get a response on the test dataset
	int testMissed = 0;
	for (int i = 0; i < testset[0].rows; i++)
	{
		double response = knn.predict(testset[0].submat(i));
		if (response != testset[1][i])
		{
			testMissed++;
		}
	}

	// Show the classification results
	cout << "Error Rate on Trainset : " << (double)trainMissed / trainset[0].rows << endl;
	cout << "Error Rate on Testset : " << (double)testMissed / testset[0].rows << endl;
}

// The Naive Bayesian Classifier
void test_naivebayes(string trainPath, string testPath)
{
	// Load the dataset
	mlldataset trainset(trainPath, ",", LABEL_REAR);
	mlldataset testset(testPath, ",", LABEL_REAR);

	// Train the dataset
	naivebayes nb;
	nb.train(trainset);
	nb.save("..\\naive_bayesian_result.ini");
// 	nb.open("..\\naive_bayesian_result.ini");

	// Get a response on the train dataset
	int trainMissed = 0;
	for (int i = 0; i < trainset[0].rows; i++)
	{
		double response = nb.predict(trainset[0].submat(i));
		if (response != trainset[1][i])
		{
			trainMissed++;
		}
	}

	// Get a response on the test dataset
	int testMissed = 0;
	for (int i = 0; i < testset[0].rows; i++)
	{
		double response = nb.predict(testset[0].submat(i));
		if (response != testset[1][i])
		{
			testMissed++;
		}
	}

	// Show the classification results
	cout << "Error Rate on Trainset : " << (double)trainMissed / trainset[0].rows << endl;
	cout << "Error Rate on Testset : " << (double)testMissed / testset[0].rows << endl;
}
