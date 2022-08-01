/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

var myMessage1 = ["Do you want to know more about this codebase example?", 
    "Hover over a property to see what it means. More information, links, and learning tips will be added soon! "];
var myMessage2 = ["Click Me!", "Hide Me!"];
var playButton1Txt = ["Play", "Stop"];
var directionButton1Txt = ["Left to Right", "Right to Left"];

var slidePanel1ActiveFlag = false;
var playButton1Flag = false;
var directionButton1Flag = 0; // right to left

var mySim1;
var myTimer1;

var mySim2;
var myTimer2;

$(document).ready(function(){
    $("#panel").slideUp(1);
    modifySlidePanelMessages(slidePanel1ActiveFlag);
    
    $('[data-toggle="tooltip"]').tooltip();  
    
    $("#playButton1Text").html(playButton1Txt[0]);
    $("#dirButton1Text").html(directionButton1Txt[0]);
    
    //drawOnCanvas1();
    /*   
    $("#canvas2Border").wave({
        width: 320,
        amplitude: 127,
        color: "yellow",
        thickness: 2,
        bgColor: "gray",
        phase: 180,
        grid: true,
        gridThickness: 0.5
    });
    
    
    $("#canvas3Border").wave({
        width: 250,
        amplitude: 63,
        color: "yellow",
        thickness: 2,
        bgColor: "gray",
        phase: 180,
        grid: true,
        gridThickness: 0.5
    });*/
    
    //animateWave($("#canvas2"),false,O1);
    //mySim2 = animateWave($('#canvas2')[0], false, O2, true);
    
    $(".btn-slide").click(function(){
	$("#panel").slideToggle("slow");
        $(this).toggleClass("active"); 
        slidePanel1ActiveFlag = !slidePanel1ActiveFlag;
        modifySlidePanelMessages(slidePanel1ActiveFlag);
        //draw();
    });	 
    
    //------------play/stop button----------------------------
    $("#playButton1").hover(function(){
       $("#playButton1Text").css("color","yellow"); 
    }, function(){
       $("#playButton1Text").css("color","white");  
    });
    
    $("#playButton1").mousedown(function(){
       $("#playButton1Text").css("color","black"); 
    });
    
    $("#playButton1").mouseup(function(){
       $("#playButton1Text").css("color","white"); 
    });
    
    $("#playButton1").click(function(){
        playButton1Flag = !playButton1Flag;
        if(playButton1Flag){
            $("#playButton1Text").html(playButton1Txt[1]);
            $(this).css("background-color","red");            
            mySim1 = animateWave($('#canvas1')[0], myTimer1, O1);
        }
        else{
            $("#playButton1Text").html(playButton1Txt[0]);
            $(this).css("background-color","green");
            //animateWave($('#canvas1')[0]);            
            clearInterval(mySim1);
        }
    });
    
    //------------direction button----------------------------
    
    $("#dirButton1").hover(function(){
       $("#dirButton1Text").css("color","yellow"); 
    }, function(){
       $("#dirButton1Text").css("color","white");  
    });
    
    $("#dirButton1").mousedown(function(){
       $("#dirButton1Text").css("color","black"); 
    });
    
    $("#dirButton1").mouseup(function(){
       $("#dirButton1Text").css("color","white"); 
    });
    
    $("#dirButton1").click(function(){
        directionButton1Flag = !directionButton1Flag;
        if(directionButton1Flag){
            $("#dirButton1Text").html(directionButton1Txt[1]);
            $(this).css("background-color","orangered");
            O1.w = .002;
        }
        else{
            $("#dirButton1Text").html(directionButton1Txt[0]);
            $(this).css("background-color","#006699");
            O1.w = -.002;
        }
    });
    
});



function modifySlidePanelMessages(flag){
    if(flag){        
        $("#slidePanelMessage1").html(myMessage1[1]);
        $("#slidePanelMessage2").html(myMessage2[1]);
    }
    else{
        $("#slidePanelMessage1").html(myMessage1[0]);
        $("#slidePanelMessage2").html(myMessage2[0]);
    }
}

function drawOnCanvas1(){
    var canvas = document.getElementById("canvas1");
    var ctx = canvas.getContext("2d");
    //ctx.fillStyle = "#FF0000";
    //ctx.fillRect(0,0,150,75);
    //$("#canvas1").wave();
    //canvas.wave();
    var imageObj = new Image();    
    imageObj.onload = function(){
        ctx.drawImage(imageObj, 0,0);
    };
    imageObj.src = 'images/scopeWidgetOnDisplay.png';
}