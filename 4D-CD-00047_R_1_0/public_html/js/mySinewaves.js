/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

// parameters for sim1
var O1 = {
    a: 1.5,
    k: 3,
    //w: .005
    //w: -.005
    w: -.002,
    curveColor: "lime",
    t: 0
};

var O2 = {
    a: 1.5,
    k: 3,
    //w: .005
    //w: -.005
    w: -.002,
    curveColor: "blue",
    t: 0
};



var axisColor = "rgb(128, 128, 128)";
var wind = 1;
var tSteps = 100;
var dt = 100;


function showAxes(ctx, axes) {
    var w = ctx.canvas.width;
    var h = ctx.canvas.height;

    ctx.beginPath();
    ctx.strokeStyle = axisColor;
    // X axis
    ctx.moveTo(0, axes.t0);
    ctx.lineTo(w, axes.t0);
    // Y axis
    ctx.moveTo(axes.s0, 0);
    ctx.lineTo(axes.s0, h);
    ctx.stroke();
}

//var t = 0;

function animateWave(canvas, timer, param, axesFlag) {
    var fy = function(x, t) {
        return param.a * Math.sin(param.k * x - param.w * t);
    };
    var ctx = canvas.getContext("2d");
    // pixels from x=0 to x=1
    var scaleX = .5 * canvas.width;
    var scaleY = .3 * canvas.height;
    //var t = 0;
    var axes = {
        s0: .5 * canvas.width,
        // t0 pixels from top to y=0
        t0: .5 * canvas.height
    };
    var xs = function(s) {
        return (s - axes.s0) / scaleX;
    };
    var yt = function(t) {
        return (axes.t0 - t) / scaleY;
    };
    var sx = function(x) {
        return x * scaleX + axes.s0;
    };
    var ty = function(y) {
        return axes.t0 - y * scaleY;
    };
    var ds = canvas.width / tSteps;
    var dx = xs(ds) - xs(0);

    function wave(t) {
        var i = 0;
        var x = xs(0);
        var y = fy(x, t);


        ctx.beginPath();
        ctx.lineWidth = 1;
        //ctx.strokeStyle = "rgb(255, 0, 0)";
        //ctx.strokeStyle = "lime";
        ctx.strokeStyle = param.curveColor;
        ctx.moveTo(sx(x), ty(y)); //debuggged

        while (i < tSteps) {
            x += dx;
            y = fy(x, t);
            ctx.lineTo(sx(x), ty(y));
            i++;
        }
        ctx.stroke();
    }

    // draw function under axes
    ctx.globalCompositeOperation = 'destination-over';

    // Draw a single frame on page load
    // clear canvas
    ctx.clearRect(0, 0, 464, 288);
    //drawOnCanvas1(ctx);
    if(axesFlag)
        showAxes(ctx, axes);
    wave(param.t);

    if (timer === false)
        return null;

    // Turn off animation
    if (timer)
        return clearInterval(timer);

    return setInterval(function() {
        param.t += dt;
        ctx.clearRect(0, 0, 464, 288);
        //drawOnCanvas1(ctx);
        if(axesFlag)
            showAxes(ctx, axes);
        wave(param.t);
    }, dt);
}

