package com.example.servlets;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

//P(Event|Evidence) = P(Evidence|Event)*P(Event)/P(Evidence)
public class Table {
	private int total;//total number of words processed
	private HashMap<String,Integer[]> words;
	private int[] evidence;//holds the count of the total word given scores 1-5 mapped to the index of the array
	public Table(int score){
		//default initalize the number of rows to 10
		this.evidence = new int[score];
		words = new HashMap<String,Integer[]>();
		this.total = 0;
	}
	public double probEvent(String word, int score){
		if(words.get(word).equals(null)){
			return -1;
		}
		return ((double)words.get(word)[score-1])/sumCol(score);
	}
	public void updateTotal(){
		total++;
	}
	public int total(){
		return total;
	}
	
	public void updateScore(int score){
		evidence[score-1]++;
	}
	public void addElement(String word, int score){
		//if word is not found in map
		if(words.get(word)==null){
			//update table
			Integer[] arr = new Integer[5];
			for(int i=0;i<arr.length;i++){
				arr[i]=0;
			}
			arr[score-1]++;//score 1-5 mapped to index 0-4
			words.put(word,arr);
		}
		else{
			words.get(word)[score-1]++;
		}
	}
	public int sumRow(String word){
		int sum = 0;
		Integer[] row = words.get(word);
		for(int cout: row){
			sum = sum + cout;
		}
		return sum;
		
	}
	public HashMap<String,Integer[]> table(){
		return words;
	}
	//returns the total number of reviews with score
	public int sumCol(int score){
		return evidence[score-1];
	}
	public void printTable(){
		System.out.println("Word     "+"1  "+"2  "+"3  "+"4  "+"5  ");
		for(String key: words.keySet()){
			System.out.print(key+"      ");
			for(int num: words.get(key)){
				System.out.print(num+"  ");
			}
			System.out.println();
		}
	}
	public static void main(String[] args){
		HashMap<String,Integer[]> words = new HashMap<String,Integer[]>();
		System.out.println(words.get("hello"));
		Table tab = new Table(5);
		tab.addElement("hello", 1);
		tab.addElement("hello", 1);
		tab.addElement("wassup", 2);
		tab.printTable();
		System.out.println(tab.sumRow("hello"));
		System.out.println(tab.sumCol(2));
		
	}
	

}
