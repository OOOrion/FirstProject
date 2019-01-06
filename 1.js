var canvas = document.getElementById('c1');
var ctx = canvas.getContext('2d');

canvas.onmousemove = function(event){
	var x = event.offSetX;
  var y = event.offSetY;
  ctx.fillRect(x-5, y-5, 10, 10);
  ctx.fillStyle = 'green';
}
