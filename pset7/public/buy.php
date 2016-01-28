<?php

//configuration
require("../includes/config.php");

// if user reached page via GET (as by clicking a link or via redirect)
if ($_SERVER["REQUEST_METHOD"] == "GET")
{
    //render form   
    render("buy_form.php", [ "title" => "Buy" ]);
}

// else if user reached page via POST (as by submitting a form via POST)
else if ($_SERVER["REQUEST_METHOD"] == "POST")
{
    $symbol = strtoupper($_POST["symbol"]);
    $shares = $_POST["shares"];

    if(empty($symbol))
    {
        apologize("Please enter a symbol.");
    }
    if(empty($shares))
    {
        apologize("Please enter some shares.");
    }
    if(is_numeric($shares))
    {
        $result = preg_match("/^\d+$/",$shares);
        if($result === false)
        {
            apologize("Please enter shares as non-negative integers.");
        }
        $stock = lookup($symbol);
        if($stock === false)
        {
            apologize("Qoute is not valid");
        }
        $cash = query("SELECT cash FROM users WHERE id = ?",$_SESSION["id"]) ;
        $required = number_format($stock["price"] , 4) * $shares ;
        if($required > $cash[0]["cash"]) 
        {
            apologize("You don't have enough cash.");
        }
        $cash = $cash[0]["cash"] - $required ;        
        query("INSERT INTO portfolios (id, symbol, shares) VALUES(?, ?,  ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)",$_SESSION["id"],$symbol,$shares); 
        query("UPDATE users SET cash = ? WHERE id = ?", $cash , $_SESSION["id"]);
        query("INSERT INTO history (id, symbol, shares, price , time , transaction) VALUES(?, ?, ? , ? , NOW() , ?)",$_SESSION["id"],$symbol,$shares,$stock["price"],"BUY");           
        redirect("/"); 
    }
    else
    {
        apologize("Shares seem non-numeric.");
    }      
}
?>
