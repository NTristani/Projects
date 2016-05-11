package com.example.servlets;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;

//This class handles writing and reading reviews to/from the text file
public class WriteReview {
	private TrainBayes train;
	public WriteReview(){
		train = new TrainBayes();
	}
	//This method writes the reviews and their scores to the text file
	public void writeToFile(String name, String review, String filepath) throws IOException{
		PrintWriter write = new PrintWriter(new FileWriter(new File(filepath+"\\test.txt"),true));
		String[] splitReview = review.split("\\s+");
		int score = train.classify(splitReview, 5);//Calculate review score
		write.write(name+","+review+","+score+"\r\n");
		write.close();
	}
	//This method reads the reviews from the text file and returns its contents as a string
	public ArrayList<String> readFile(String filepath) throws IOException{
		ArrayList<String> result = new ArrayList<String>();
		FileReader myfile = new FileReader(filepath+"\\test.txt");
		BufferedReader read = new BufferedReader(myfile);
		String readLine = read.readLine();
		while(readLine != null){
			String[] info = readLine.split(",");
			result.add("Restaurant: "+info[0]+" "+"Review: "+info[1]+" "+"Score: "+info[2]);
			readLine = read.readLine();
		}
		return result;
	}
	public static void main(String[] args){
		System.out.println(System.getProperty("user.dir"));
	}
}
