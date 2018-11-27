const char webpage[] PROGMEM = R"=====(
<!DOCTYPE html> 
<html>
<head>
    <title></title>
 <style type="text/css">
    html{
      text-align: center;
      font-family: 'Lato', sans-serif;
      background: -webkit-radial-gradient(circle,#F0F9EA,#DEE5E5);
background: -o-radial-gradient(circle,#F0F9EA,#DEE5E5);
background: -moz-radial-gradient(circle,#F0F9EA,#DEE5E5);
background: radial-gradient(circle,#F0F9EA, #DEE5E5);
    }
    h1{
      text-align: center;
    }
    h2{
      text-align:center;
      color:#FF686B;
  
    }
    .right{
      width: 100%;
      padding-right: 9%;
      padding-left:9%;
      float: left;
    }
    .warn{
margin-top: 49%;
      width: 100%;
    }
    table{
      float: left;
      width: 24%;
      margin-right:2%; 
      margin-left:2%;
      margin-top: 4%;
      box-sizing: border-box;
      border-radius: 7px; 
      border:0.1px solid #C8C8C8;
      color: gray;


    }
    #dist{
      margin-left: 22%;
      margin-right: 22%;
      width: 36%;
    }

    table:hover{
        box-shadow: 0 0 19px 0px
        rgba(0,0,0,0.36);
      }
    td{
      padding: 10px;
      height: 20px;
    }
    .sname{
      color: #3D1C17;
      background-color: #2AB7CA;
      border-radius: 7px 7px 0 0 ;
      padding: 15px;
    }
    .snamed{
      color:#3D1C17;
      background-color: #FFB200;
      border-radius: 7px 7px 0 0;
      padding: 15px;
    }
    

  </style>
</head>
<body>
  <h1>Smart Sickbed Web Page</h1>
    <div class="right">
    <table id="dist">
      <tr>
        <th class="snamed" colspan="8">Distance</th>
      </tr>
      <tr>
        <th>dist1</th>
        <td id="dist1"></td>
        <th>dist3</th>
        <td id="dist3"></td>
        <th>dist2</th>
        <td id="dist2"></td>
        <th>dist4</th>
        <td id="dist4"></td>
      </tr>
    </table>

    <table>
      <tr>
        <th class="sname" colspan="2">Sensor1</th>
      </tr>
      <tr>
        <th>humd1</th>
        <td id="humd1"></td>
      </tr>
      <tr>
        <th>temp1</th>
        <td id="temp1"></td>

      </tr>
      <tr>
        <th>pres1</th>
        <td id="pres1"></td>
      </tr>

    </table>
    <table>
      <tr>
        <th class="sname" colspan="2">Sensor2</th>
      </tr>
      <tr>
        <th>humd2</th>
        <td id="humd2"></td>
      </tr>
      <tr>
        <th>temp2</th>
        <td id="temp2"></td>

      </tr>
      <tr>
        <th>pres2</th>
        <td id="pres2"></td>
      </tr>

    </table>
    <table>
      <tr>
        <th class="sname" colspan="2">Sensor3</th>
      </tr>
      <tr>
        <th>humd3</th>
        <td id="humd3"></td>
      </tr>
      <tr>
        <th>temp3</th>
        <td id="temp3"></td>

      </tr>
      <tr>
        <th>pres3</th>
        <td id="pres3"></td>
      </tr>

    </table>
    <table>
      <tr>
        <th class="sname" colspan="2">Sensor4</th>
      </tr>
      <tr>
        <th>humd4</th>
        <td id="humd4"></td>
      </tr>
      <tr>
        <th>temp4</th>
        <td id="temp4"></td>

      </tr>
      <tr>
        <th>pres4</th>
        <td id="pres4"></td>
      </tr>

    </table>
    <table>
      <tr>
        <th class="sname" colspan="2">Sensor5</th>
      </tr>
      <tr>
        <th>humd5</th>
        <td id="humd5"></td>
      </tr>
      <tr>
        <th>temp5</th>
        <td id="temp5"></td>

      </tr>
      <tr>
        <th>pres5</th>
        <td id="pres5"></td>
      </tr>

    </table>
    <table>
      <tr>
        <th class="sname" colspan="2">Sensor6</th>
      </tr>
      <tr>
        <th>humd6</th>
        <td id="humd6"></td>
      </tr>
      <tr>
        <th>temp6</th>
        <td id="temp6"></td>

      </tr>
      <tr>
        <th>pres6</th>
        <td id="pres6"></td>
      </tr>

    </table>
    
    </div>
    <div class="warn"><h2 id="warning"></h2></div>
    </div>

<script>
var h1 = setInterval(function() {loadData("humd1.txt",updateHumd1)}, 100);
var h2 = setInterval(function() {loadData("humd2.txt",updateHumd2)}, 100);
var h3 = setInterval(function() {loadData("humd3.txt",updateHumd3)}, 100);
var h4 = setInterval(function() {loadData("humd4.txt",updateHumd4)}, 100);
var h5 = setInterval(function() {loadData("humd5.txt",updateHumd5)}, 100);
var h6 = setInterval(function() {loadData("humd6.txt",updateHumd6)}, 100);

var t1 = setInterval(function() {loadData("temp1.txt",updateTemp1)}, 100);
var t2 = setInterval(function() {loadData("temp2.txt",updateTemp2)}, 100);
var h3 = setInterval(function() {loadData("temp3.txt",updateTemp3)}, 100);
var t4 = setInterval(function() {loadData("temp4.txt",updateTemp4)}, 100);
var t5 = setInterval(function() {loadData("temp5.txt",updateTemp5)}, 100);
var t6 = setInterval(function() {loadData("temp6.txt",updateTemp6)}, 100);

var p1 = setInterval(function() {loadData("pres1.txt",updatePres1)}, 100);
var p2 = setInterval(function() {loadData("pres2.txt",updatePres2)}, 100);
var p3 = setInterval(function() {loadData("pres3.txt",updatePres3)}, 100);
var p4 = setInterval(function() {loadData("pres4.txt",updatePres4)}, 100);
var p5 = setInterval(function() {loadData("pres5.txt",updatePres5)}, 100);
var p6 = setInterval(function() {loadData("pres6.txt",updatePres6)}, 100);

var d1 = setInterval(function() {loadData("dist1.txt",updatedist1)}, 100);
var d2 = setInterval(function() {loadData("dist2.txt",updatedist2)}, 100);
var d3 = setInterval(function() {loadData("dist3.txt",updatedist3)}, 100);
var d4 = setInterval(function() {loadData("dist4.txt",updatedist4)}, 100);

// var warn = setInterval(function() {loadData("warning.txt",updatewarning)}, 100);

function loadData(url, callback){
var xhttp = new XMLHttpRequest();
xhttp.onreadystatechange = function(){
if(this.readyState == 4 && this.status == 200){
callback.apply(xhttp);
}
};
xhttp.open("GET", url, true);
xhttp.send();}
function updateHumd1(){document.getElementById("humd1").innerHTML = this.responseText;}
function updateHumd2(){document.getElementById("humd2").innerHTML = this.responseText;}
function updateHumd3(){document.getElementById("humd3").innerHTML = this.responseText;}
function updateHumd4(){document.getElementById("humd4").innerHTML = this.responseText;}
function updateHumd5(){document.getElementById("humd5").innerHTML = this.responseText;}
function updateHumd6(){document.getElementById("humd6").innerHTML = this.responseText;}

function updateTemp1(){document.getElementById("temp1").innerHTML = this.responseText;}
function updateTemp2(){document.getElementById("temp2").innerHTML = this.responseText;}
function updateTemp3(){document.getElementById("temp3").innerHTML = this.responseText;}
function updateTemp4(){document.getElementById("temp4").innerHTML = this.responseText;}
function updateTemp5(){document.getElementById("temp5").innerHTML = this.responseText;}
function updateTemp6(){document.getElementById("temp6").innerHTML = this.responseText;}

function updatePres1(){document.getElementById("pres1").innerHTML = this.responseText;}
function updatePres2(){document.getElementById("pres2").innerHTML = this.responseText;}
function updatePres3(){document.getElementById("pres3").innerHTML = this.responseText;}
function updatePres4(){document.getElementById("pres4").innerHTML = this.responseText;}
function updatePres5(){document.getElementById("pres5").innerHTML = this.responseText;}
function updatePres6(){document.getElementById("pres6").innerHTML = this.responseText;}

function updatedist1(){document.getElementById("dist1").innerHTML = this.responseText;}
function updatedist2(){document.getElementById("dist2").innerHTML = this.responseText;}
function updatedist3(){document.getElementById("dist3").innerHTML = this.responseText;}
function updatedist4(){document.getElementById("dist4").innerHTML = this.responseText;}

// function updatewarning(){document.getElementById("warning").innerHTML = this.responseText;}
</script>
</HTML>
)=====";
