<form action="sell.php" method="post">
    <div class = "form-group">
            <label >SELL</label>
            <select class="form-control" name = "sell">
                <?php  foreach ($positions as $position) : ?>
                <option><?= $position["symbol"] ?></option>
                <?php endforeach ?>
             </select>
    </div>
    <div class="form-group">
            <button type="submit" class="btn btn-default">SELL SHARES</button>
    </div>    
</form>

