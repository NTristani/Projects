package com.example.servlets;

public class ProjectRun {
	public static void main(String[] args){
		//trains the model
		System.out.println(System.getProperty("user.dir"));
		TrainBayes train = new TrainBayes();
		String[] test = {"food","good"};
		//this should output the score for a review
		train.classify(test, 5);
		System.out.println(train.classify(test, 5));
	}
}
