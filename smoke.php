<?php
$conn = mysqli_connect("localhost","root","","Motion_db");

$data = json_decode(file_get_contents("php://input"), true);

if($data){

    $smoke = $data["smoke"];
    $temperature = $data["temperature"];

    mysqli_query($conn,
    "INSERT INTO sensor_data(smoke,temperature)
     VALUES('$smoke','$temperature')");

    echo "Inserted";

}else{
    echo "No data";
}
?>