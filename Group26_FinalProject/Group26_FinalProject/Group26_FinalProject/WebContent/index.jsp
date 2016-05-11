<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" 
    "http://www.w3.org/TR/html4/loose.dtd">
<html>
<style type="text/css">
body {
    background-image:
        "/ExampleWebProject/congruent_outline.css";
}
</style>
 
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>Review it!</title>
    <link rel="stylesheet" href="/ExampleWebProject/style.css">
</head>
<body>
    <body background= "/ExampleWebProject/congruent_outline.png">
	<h1>Review It!</h1>

	<h2><center>Your feedback is important to us!</center></h2>

    <h3><center>Please enter the restaurant's name and write a review of the restaurant and your meal!</center>
    <center>
        <img src="https://lh5.googleusercontent.com/GdfdwCPEHnwKtmSxpgK15-gyM-Knl2tfoSm6QIhUazBRKA4hO_iatlkLtD_gCoIPtTsmiNKHqsTSDCtSf4d18OIBjUXBn9FVi0Wtc7iCLUaS8bv_o04xgitfy3P32TT_yP0myKuQUDIbxk3h" width="240" height="120">
        <img src="http://hdwallpapershoot.com/wp-content/uploads/2015/03/Thai-Food-Wallpaper-71.jpg" width="240" height="120">
        <img src="https://i.ytimg.com/vi/3LZR_gmfii4/maxresdefault.jpg" width="240" height="120">
    </center>
</center>
<form id="contact-form" action="HelloWorld" method="GET">

    <p><center>Restaurant Name:</center></p>
    <p><center><input type="text" placeholder="Name" name="username"></center></p>

    <p><center>Comments: </center></p>
    <p><center><textarea name="review" placeholder="Be nice!" rows="5" cols="70"></textarea></center></p>
    <p><center><input type="submit"></center></p>

</form>
<center><font size="5">Thank you for your feedback!</font><br /></center>
<br><br><br><br><br><br><br><br>
<center>
    <form action="Manager">
        <input type="submit" value="Managers Portal">
    </form>
</center>


</body>
</html>