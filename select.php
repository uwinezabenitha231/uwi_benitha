<?php
include("insert.php");

// Select data
$select = mysqli_query($conn, "SELECT * FROM motion_table");
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Motion Detection System</title>

    <style>

        body{
            font-family: Arial, sans-serif;
            background:#f4f4f4;
            margin:0;
            padding:20px;
        }

        .container{
            width:80%;
            margin:auto;
            background:white;
            padding:20px;
            border-radius:10px;
            box-shadow:0px 0px 10px rgba(0,0,0,0.2);
        }

        h1{
            text-align:center;
            color:#333;
        }

        table{
            width:100%;
            border-collapse:collapse;
            margin-top:20px;
        }

        table th{
            background:#007bff;
            color:white;
            padding:12px;
        }

        table td{
            padding:10px;
            text-align:center;
            border:1px solid #ddd;
        }

        tr:nth-child(even){
            background:#f2f2f2;
        }

        .status{
            text-align:center;
            font-size:18px;
            margin-top:10px;
            color:green;
        }

        .btn{
            display:block;
            margin:auto;
            margin-top:20px;
            padding:10px 20px;
            background:#28a745;
            color:white;
            border:none;
            border-radius:5px;
            cursor:pointer;
            font-size:16px;
        }

        .btn:hover{
            background:#218838;
        }

    </style>
</head>

<body>

<div class="container">

    <h1>Motion Detection Monitoring System</h1>

    <div class="status" id="status">
        Loading data...
    </div>

    <button class="btn" onclick="loadData()">Refresh Data</button>

    <table>
        <thead>
            <tr>
                <th>ID</th>
                <th>Motion Detected</th>
                <th>Timestamp</th>
            </tr>
        </thead>

        <tbody id="table-data">

        <?php
        if ($select && mysqli_num_rows($select) > 0){

            while($row = mysqli_fetch_assoc($select)){
        ?>

            <tr>
                <td><?php echo $row['id']; ?></td>
                <td><?php echo $row['motion_detected']; ?></td>
                <td><?php echo $row['timestamp']; ?></td>
            </tr>

        <?php
            }

        } else {
            echo "<tr><td colspan='3'>No Data Available</td></tr>";
        }
        ?>

        </tbody>

    </table>

</div>

<script>

function loadData(){

    var xhr = new XMLHttpRequest();

    xhr.open("GET", "fetch.php", true);

    xhr.onload = function(){

        if(this.status == 200){

            document.getElementById("table-data").innerHTML = this.responseText;

            document.getElementById("status").innerHTML = "Data Loaded Successfully";
        }
        else{
            document.getElementById("status").innerHTML = "Failed to Load Data";
        }
    };

    xhr.send();
}

// Auto refresh every 5 seconds
setInterval(loadData, 5000);

</script>

</body>
</html>