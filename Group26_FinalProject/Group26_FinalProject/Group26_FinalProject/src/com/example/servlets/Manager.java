package com.example.servlets;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Servlet implementation class Manager
 */
@WebServlet("/Manager")
public class Manager extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public Manager() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		response.setContentType("text/html");
		PrintWriter pw = response.getWriter();
		//Print out the header
		pw.write("<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\"" +
			"http://www.w3.org/TR/html4/loose.dtd\">\n" +
			"<html> \n" +
            "<head> \n" +
              "<meta http-equiv=\"Content-Type\" content=\"text/html; " +
                "charset=ISO-8859-1\"> \n" +
              "<title> Review It!  </title> \n" + "<link rel=stylesheet href=/ExampleWebProject/style.css> \n" +
            "</head> \n" +
            "<body>  <body background= /ExampleWebProject/congruent_outline.png>  <div align='center'> \n" +
            "<h1>Manager Portal</h1>" + "<center> \n" + "<font size=5 font color=white>All reviews can be located here</font><br/>" +
            "<br>" +
            "</body> \n" + "</html>"
				);
		//Create a WriteReview object to read the reviews from the text file
		WriteReview wr = new WriteReview();
		ArrayList<String> output = wr.readFile(System.getProperty("user.dir"));
		//Print out the
		for(String s : output){
			pw.write("<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\"" +
                    "http://www.w3.org/TR/html4/loose.dtd\">\n" +
                "<html> \n" +
                  "<head> \n" +
                    "<meta http-equiv=\"Content-Type\" content=\"text/html; " +
                      "charset=ISO-8859-1\"> \n" +
                    "<title> Review It!  </title> \n" + "<link rel=stylesheet href=/ExampleWebProject/style.css> \n" +
                  "</head> \n" +
                  "<body>  <body background= /ExampleWebProject/congruent_outline.png>  <div align='center'> \n" +
                    "<style= \"font-size=\"12px\" color:white\"\">" +
                      "<font color=white>"+s+"</font>" + "<br>" + "<br>" +
                  "</font></body> \n" +
                "</html>");
		}
		pw.write("<form action=index.jsp> \n" +
                      "<input type=submit value=Return> \n" + "</form></center> \n");
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
	}

}
