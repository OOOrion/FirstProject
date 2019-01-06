var canvas = document.getElementById('c1');
var ctx = canvas.getContext('2d');
var balls = [];

var timeoutID;


var Ball = function(ctx, name, color, x, y, r){
  this.name = name;
  this.x = x;
  this.y = y;
  this.r = r;
  this.ctx = ctx;
  this.color = color;
};


Ball.prototype.show = function(){
  this.ctx.arc(this.x, this.y, this.r, 0, 2*Math.PI);
  this.ctx.fillStyle = this.color;
  this.ctx.fill();
  this.ctx.strokeStyle = 'black';
  this.ctx.lineWidth = 5;
  this.ctx.stroke();
  this.ctx.beginPath();
};

Ball.prototype.del = function(){
  this.ctx.arc(this.x, this.y, this.r, 0, 2*Math.PI);
  this.ctx.fillStyle = 'white';
  this.ctx.fill();
  this.ctx.strokeStyle = 'white';
  this.ctx.lineWidth = 100;
  this.ctx.stroke();
  this.ctx.beginPath();
}

var b1 = new Ball(ctx, 'ball', 'green', 100, 100, 50);
for (i=0;i<40;i++){
  var st = true;
  var x = rand(50, 1800);
  var y = rand(50, 850);
  for (var b in balls){
    if (range(x, y, balls[b].x, balls[b].y)<=2*balls[b].r+10){
      i-=1;
      st = false;
      break;
    }
  }
  if (st){
    balls.push(new Ball(ctx, 'ball-'+i.toString(), 'blue', x, y, 25));
  }
}

for (var b in balls){
  balls[b].show();
}

b1.show();

function isInBall(x, y, ball){
  if (Math.pow(x-ball.x, 2)+Math.pow(y-ball.y, 2)<=Math.pow(ball.r, 2)){return true;}
  else {return false;}
};

canvas.onmousedown = function(event){
  var x = event.offsetX;
  var y = event.offsetY;
  if (isInBall(x, y, b1)) {
    clearTimeout(timeoutID);
    canvas.onmousemove = function(event){
      var x = event.offsetX;
      var y = event.offsetY;
      b1.del();
      for (var b in balls){
        b1.eat(balls[b]);
      }
      for (var b in balls){
        balls[b].show();
      }
      b1.x = x;
      b1.y = y;
      b1.show();
    }
    canvas.onmouseup = function(event){
      canvas.onmousemove = null;
      clearTimeout(timeoutID);
      bot(b1);
    }
  }
}

function rand(mn, mx){
  return (Math.round(mn + Math.random()*(mx-mn)), Math.round(mn + Math.random()*(mx-mn)));
}

function range(x1, y1, x2, y2){
  return Math.sqrt(Math.pow((x1-x2), 2)+Math.pow((y1-y2), 2));
}

Ball.prototype.eat = function(ball){
  if (this.r>=ball.r*0.9){
    if (range(this.x, this.y, ball.x, ball.y)<=this.r-ball.r){
      delete balls[balls.indexOf(ball)];
      ball.del();
      this.r+=Math.round(Math.sqrt(Math.pow(this.r, 2)+Math.pow(ball.r, 2))-this.r);
      this.show();
    }
  }
}

Ball.prototype.goto = function(x, y, gxx, gyy){
  if (range(this.x, this.y, x, y)<=this.r-26){
    bot(this);
  }
  else{
    for (var b in balls){
      b1.eat(balls[b]);
     }
    this.del();
    for (var b in balls){
      balls[b].show();
     }
    
    var d = range(this.x, this.y, x, y);
    var dx = x - this.x;
    var dy = y - this.y;
    if (gxx==null && gyy==null){
      gx = dx/d;
      gy = dy/d;
    }
    
    this.x+=gx;
    this.y+=gy;
    this.show();
    timeoutID = setTimeout(function() {this.goto(x, y, gx, gy);}.bind(this), 5);
  }
}


function bot (ball){
  var gx = null;
  var gy = null;
  var mn = 1000000;
  var aim = null;
  for (b in balls){
    if (range(ball.x, ball.y, balls[b].x, balls[b].y)<mn) {
      mn = range(ball.x, ball.y, balls[b].x, balls[b].y);
      aim = balls[b];
    }
  }
  var tx = aim.x;
  var ty = aim.y;
  ball.goto(tx, ty, gx, gy);
}

bot(b1);
