package com.example.servlets;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Servlet implementation class HelloWorld
 */
@WebServlet("/HelloWorld")
public class HelloWorld extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public HelloWorld() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		WriteReview wr = new WriteReview();
		String username = request.getParameter("username");
        String review = request.getParameter("review");
        System.out.println(System.getProperty("user.dir"));
        wr.writeToFile(username, review, System.getProperty("user.dir"));
        System.out.println(System.getProperty("java.ext.dirs"));
		PrintWriter out = response.getWriter();

		out.println (
                "<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\"" +
                    "http://www.w3.org/TR/html4/loose.dtd\">\n" +
                "<html> \n" +
                  "<head> \n" +
                    "<meta http-equiv=\"Content-Type\" content=\"text/html; " +
                      "charset=ISO-8859-1\"> \n" +
                    "<title> Review It!  </title> \n" + "<link rel=stylesheet href=/ExampleWebProject/style.css> \n" +
                  "</head> \n" +
                  "<body>  <body background= /ExampleWebProject/congruent_outline.png> <div align='center'> \n" +
                  "<h1>Thank you for your input!</h1>" +
                    "<style= \"font-size=\"12px\" color:white\"\">" +
                      "<font color=white>"+"Username: " + username + " <br> " + 
                      "Review: " + review + " <br> " + "Review successfully submitted!" +"</font>"+
                      "<br><br><br><br>" + "<center> \n" + "<form action=index.jsp> \n" +
                      "<input type=submit value=Return> \n" + "</form></center> \n" +
                  "</font></body> \n" +
                "</html>" 
              );
		
		
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
	}

}
