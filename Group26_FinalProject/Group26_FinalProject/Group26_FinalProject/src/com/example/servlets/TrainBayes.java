package com.example.servlets;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Scanner;
import java.util.List;
//bayes model for text base processing
//P(Event|Evidence) = P(Evidence|Event)*P(Event)/P(Evidence)
public class TrainBayes {
	private Table table;
	private ArrayList<Review> reviews;
	public TrainBayes(String[] words, int[] scores){
		if(words.length!=scores.length){
			System.out.println("array length do not match");
		}
		else{
			table = new Table(5);
			for(int i=0;i<words.length;i++){
				 table.addElement(words[i], scores[i]);
			}
			table.updateScore(1);
			table.updateScore(1);
			table.updateScore(1);
			table.updateScore(1);
			table.updateScore(2);
			table.updateScore(2);
			table.updateTotal();
			table.updateTotal();
			table.updateTotal();
			table.updateTotal();
			table.updateTotal();
			table.updateTotal();
			
		}

	}
	public TrainBayes(){
		table = new Table(5);
		ReadFile read = new ReadFile();
		this.reviews = read.getReviews();
		for(int i=0;i<reviews.size();i++){
			int score = reviews.get(i).score;
			for(String str: reviews.get(i).text.split(" ")){
				if((str.contains(",")||str.contains(".")||str.contains("\\?")||str.contains("\\("))){
					str= str.substring(0,str.length()-1);
				}
				if(!str.equals(" ")){
					table.addElement(str, score);
				}
			}
			//update the total number of reviews and the number of reviews under each section
			table.updateScore(score);
			table.updateTotal();
		}
	}
	//calculate score for new reviews using P(Score|Text) = P(Text|Score)*P(Score)/P(Text)
	public int classify(String[] arr, int evidence){
		//convert String array to list and iterate through it to remove the elements not present in the trained word table
		ArrayList<String> reviewWords = new ArrayList<String>();
		for(String word: arr){
			reviewWords.add(word);
		}
		Iterator<String> iter = reviewWords.iterator();
		while(iter.hasNext()){
			String s = iter.next();
			if(!table.table().keySet().contains(s)){
				iter.remove();
			}
		}
		arr = reviewWords.toArray(new String[reviewWords.size()]);

		double[] ProbScore = new double[evidence];//Prob(Score)
		for(int i =0;i<ProbScore.length;i++){
			ProbScore[i] = ((double)table.sumCol(i+1))/table.total();
		}
		
		double[] ProbTextScore = new double[evidence];//Prob(Text|Score)
		//initialize to 1 for multiplication
		for(int i=0;i<ProbTextScore.length;i++){
			ProbTextScore[i] = 1;
		}
		double ProbText = 0;//Prob(Text)
		double[] ProbFinal = new double[evidence];//P(Score|Text)
		//keep track of the index of the string array
		//loop through table of all the words
		for(String str: table.table().keySet()){
			//calculate ProbText
			for(int i=1;i<evidence+1;i++){
				//if word is in the table, then its probability of occuring in a review with given score
				//can be found by looking at the table entry
				int found =0;
				for(String review: arr){
					//if word from review is present in the table
					if(review.equals(str)){
						ProbTextScore[i-1] = ProbTextScore[i-1]*table.probEvent(str,i);
						found=1;
					}
				}
				//if word from review is not found in the table
				if(found==0){
					ProbTextScore[i-1] = ProbTextScore[i-1]*(1-table.probEvent(str,i));
				}

				
			}
		}
		//compute Prob(Text)
		for(int i=0;i<ProbScore.length;i++){
			ProbText =ProbText+ProbScore[i]*ProbTextScore[i];
		}
		//now, we calculate P(Score|Text) for each of the scores 1-5
		for(int i=0;i<ProbFinal.length;i++){
			ProbFinal[i] = ProbTextScore[i]*ProbScore[i]/ProbText;
		}
		//find max value in ProbFinal array and return; this is the most likely score predicted by Bayes
		double max = ProbFinal[0];
		int indexmax = 0;
		for(int i=1;i<ProbFinal.length;i++){
			if(ProbFinal[i]>max){
				max = ProbFinal[i];
				indexmax =i;
			}
		}
		return indexmax+1;
		
	}
	
	public static void main(String[] args){
		TrainBayes bae1 = new TrainBayes(new String[]{"password","password","password","review","review","review","send","send","send","send","us","us","us","us","your","your","your","your","account"},new int[]{1,1,2,1,2,2,1,1,1,2,1,1,1,2,1,1,1,2,1});
		bae1.table.printTable();
		System.out.println(bae1.table.sumCol(1));
		System.out.println(bae1.table.sumCol(2));
		String[] review = {"review","us","now"};
//		bae1.classify(review,5);
//		System.out.println(bae1.table.sumCol(2));
		System.out.println(bae1.classify(review,2));
		System.out.println(bae1.table.table().keySet().contains("review"));
		for(String rev: review){
			System.out.println(rev);
		}
	}
}
