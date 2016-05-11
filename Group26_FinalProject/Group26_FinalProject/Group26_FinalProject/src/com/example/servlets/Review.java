package com.example.servlets;


//This creates the Review ADT
public class Review {
	//Each review consists of one of each:
	//A Product ID
	public String productId;
	//A "helpfulness" Score
	public String helpfulness;
	//The reviews score
	public int score = 100;
	//Time of review
	public int time = 0;
	//Summary of the review
	public String summary;
	//And the review itself
	public String text;
	
	public void Review(String id, String help, int score,int time, String summary, String text){
		//Each of the explained above are in this ADT
		 this.productId = id;
		 this.helpfulness = help;
		 this.score = score;
		 this.summary = summary;
		 this.text = text;
	}
	//Checks to make sure the review is complete (Has all these elements)
	public Boolean isComplete(){
		//Does it have a product ID?
		if(this.productId==null){
			return false;
		}
		//Does it haven a helpfulness score?
		if(this.helpfulness==null){
			return false;
		}
		//Does it have a helpfulness score?
		if(this.score==100){
			return false;
		}
		//Does it have the actual review text?
		if(this.text==null){
			return false;
		}
		//If requirements met, the review is complete
		return true;
	}
	public void printReview(){
		//Prints the elements the user desires to see
		System.out.println(this.productId);
		System.out.println(this.helpfulness);
		System.out.println(this.score);
		System.out.println(this.summary);
		System.out.println(this.text);
		
	}
}
