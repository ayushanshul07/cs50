  <ul class ="nav nav-pills" id ="navig"> 
        <li><a href = "quote.php">Quote</a></li> 
        <li><a href = "sell.php">Sell</a></li>
        <li><a href = "buy.php">Buy</a></li>
        <li><a href = "history.php">History</a></li>
        <li><a href = "password.php">Change Password</a></li>
   </ul>

   <table class = "table table-striped table-hover" id = "table">
      <thead>
           <tr>
              <th>Symbol</th>
              <th>Name</th>
              <th>Shares</th>
              <th>Price</th>
              <th>Total</th>
            </tr>
      </thead>
      <tbody> 
         <?php  foreach ($positions as $position) : ?>
           <tr>
              <td><?= $position["symbol"] ?></td>
              <td><?= $position["name"] ?></td>
              <td><?= $position["shares"] ?></td>
              <td><?= '$' . $position["price"] ?></td>
              <td><?= '$' . $position["total"] ?></td>
           </tr>
         <?php endforeach ?>
            <tr>
              <td>CASH</td>
              <td></td>
              <td></td>
              <td></td>
              <td><?= '$' . $cash ?></td>
            </tr>
      </tbody>
   </table>
<div>
    <a href="logout.php">Log Out</a>
</div>
