<?php

// configuration
require("../includes/config.php"); 

$rows = query("SELECT symbol , shares from portfolios WHERE id = ?" , $_SESSION["id"]);
$cash = query("SELECT cash from users WHERE id = ?" , $_SESSION["id"]);
$cash = number_format($cash[0]["cash"] , 4);
$positions = [];
foreach ($rows as $row)
{
    $stock = lookup($row["symbol"]);
    if ($stock !== false)
    {  
        $positions[] = [
            "name" => $stock["name"],
            "price" => $stock["price"],
            "shares" => $row["shares"],
            "symbol" => $row["symbol"],
            "total" => number_format( ( $row["shares"] ) * ($stock["price"]) , 4 ) 
        ]; 
    }
}

// render portfolio
render("portfolio.php", ["cash" => $cash , "positions" => $positions , "title" => "Portfolio"]);

?>
