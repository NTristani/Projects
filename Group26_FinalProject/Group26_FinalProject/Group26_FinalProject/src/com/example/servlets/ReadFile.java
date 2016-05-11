package com.example.servlets;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;
//This class serves the purpose of reading the reviews from a file
public class ReadFile {
	private ArrayList<Review> reviews;
	public ReadFile(){
		//Creates the array list to hold the array lists of reviews
		reviews = new ArrayList<Review>();
		//Location of the review file
		File file = new File(System.getProperty("user.dir")+"\\foods.txt");
		try{
			//Creates the file scanner
			Scanner scan = new Scanner(file);
			//Initlizes first review to be scanned
			Review one = new Review();
			//While loop iterates through each review
			while(scan.hasNextLine()){
				//Holds next line
				String str = scan.nextLine();
				//Isolates the product ID
				if(str.split("product/productId:").length>1){
					one.productId= str.split("product/productId:")[1].trim();
				}
				//Isolates the "Helpfullness" string
				if(str.split("review/helpfulness:").length>1){
					one.helpfulness = str.split("review/helpfulness:")[1].trim();				
				}
				//Isolates the review score
				if(str.split("review/score:").length>1){
					one.score =(int) Double.parseDouble(str.split("review/score:")[1].trim());
				}
//				Isolates the review time
//				if(str.split("review/time:").length>1){
//					one.time = Integer.parseInt(str.split("review/time:")[1]);
//				}
				//Isolates the review summary
				if(str.split("review/summary:").length>1){
					one.summary = str.split("review/summary:")[1].trim();
				}
				//Isolates the reviews itself
				if(str.split("review/text:").length>1){
					one.text = str.split("review/text:")[1].trim();
				}
				//Checks if all of the components of the review has been added and then adds it to the review arraylist
				if(one.isComplete()==true){
					reviews.add(one);
					one = new Review();
				}

			}
		}
		//Required catch statement
		catch(FileNotFoundException ex){
			ex.printStackTrace();
		}
	}
	public ArrayList<Review> getReviews(){
		//Returns the reviews read from the file
		return reviews;
	}
}
