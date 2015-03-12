var kEPS = 10;

// represntation float to int
// for example: '-1.23' simulate '-1230000'
function fixNumber(_number, _eps) {
	_eps = _eps || kEPS;

	var arr = _number.toFixed(_eps).split('.');

	return parseInt(arr.join(''));
}

// addition
function accurateAdd(_number1, _number2, _eps) {
	_eps = _eps || kEPS;

	var add = fixNumber(_number1, _eps) + fixNumber(_number2, _eps);

	return add / Math.pow(10, _eps);
}

// subtraction
function accurateSub(_number1, _number2, _eps) {
	_eps = _eps || kEPS;

	var sub = fixNumber(_number1, _eps) - fixNumber(_number2, _eps);

	return sub / Math.pow(10, _eps);
}

// multiplication
function accurateMulti(_number1, _number2, _eps) {
	_eps = _eps || kEPS;

	var multi = fixNumber(_number1, _eps) * fixNumber(_number2, _eps),
		normalize = multi / Math.pow(10, _eps + _eps);

	return parseFloat(normalize.toFixed(_eps));
}

// division 
function accurateDiv(_number1, _number2, _eps) {
	_eps = _eps || kEPS;

	if (_number2 == 0) {
		return "Error";
	}

	return fixNumber(_number1, _eps) / fixNumber(_number2, _eps);
}



// function y'
function derivative(_x, _y) {
	return accurateAdd(accurateMulti(_x, _x), accurateMulti(_y, _y));
}

// Make nodes from _x_l to x_r_ with step
// return array
function makeNodes(_x_l, _x_r, _step) {
	var nodes = [];

	for (var x = _x_l; x <= _x_r; x = accurateAdd(x, _step)) {
		nodes[nodes.length] = x;
	}

	return nodes;
}

function picard1(_y0, _x_nodes) {
	var yNodes = [_y0],
		xxx;

	for (var i = 1; i < _x_nodes.length; i++) {
		xxx = accurateMulti(accurateMulti(_x_nodes[i], _x_nodes[i]), _x_nodes[i]);
		yNodes[i] = accurateDiv(xxx, 3);
	}

	return yNodes;
}

function picard2(_y0, _x_nodes) {
	var yNodes = [_y0],
		k1 = accurateDiv(1, 63),
		xxxx, xxx;

	for (var i = 1; i < _x_nodes.length; i++) {
		xxx = accurateMulti(accurateMulti(_x_nodes[i], _x_nodes[i]), _x_nodes[i]);
		xxxx = accurateMulti(xxx, _x_nodes[i]);
		yNodes[i] = accurateMulti(accurateMulti(k1, xxx),
								  accurateAdd(xxxx, 21));
	}

	return yNodes;
}

function picard3(_y0, _x_nodes) {
	var yNodes = [_y0],
		x15, x11, x7, x3;

	for (var i = 1; i < _x_nodes.length; i++) {
		x3 = accurateMulti(_x_nodes[i], accurateMulti(_x_nodes[i], _x_nodes[i]));
		x7 = accurateMulti(_x_nodes[i], accurateMulti(x3, x3));
		x11 = accurateMulti(_x_nodes[i], accurateMulti(x7, x3));
		x15 = accurateMulti(_x_nodes[i], accurateMulti(x7, x7));

		yNodes[i] = accurateAdd(accurateDiv(x15, 59535),
								accurateAdd(accurateDiv(x11, 1039.5),
											accurateAdd(accurateDiv(x7, 63), accurateDiv(x3, 3))));
	}

	return yNodes
}

function explicitEuler(_derivative_f, _y0, _x_nodes, _step) {
	var yNodes = [_y0];

	for (var i = 1; i < _x_nodes.length; i++) {
		yNodes[i] = accurateAdd(yNodes[i - 1], 
								accurateMulti(_step,
											  _derivative_f(_x_nodes[i - 1], yNodes[i - 1])));
	}

	return yNodes;
}

// Explicit Runge-Kutta 2 with alpha
function explicitRungeKutta2(_df, _y0, _x_nodes, _step, _alpha) {
	if (_alpha == 0) {
		return 'Error';
	}

	var yNodes = [_y0],
		k1 = accurateSub(1, _alpha),
		k2 = accurateDiv(_step, accurateMulti(2, _alpha)),
		df, ext, eext;

	for (var i = 1; i < _x_nodes.length; i++) {
		df = _df(_x_nodes[i - 1], yNodes[i - 1]);
		ext = accurateMulti(_alpha,
							_df(accurateAdd(_x_nodes[i - 1], k2), 
								accurateAdd(yNodes[i - 1], accurateMulti(k2, df))));
		eext = accurateMulti(_step,
							 accurateAdd(accurateMulti(k1, df),
										 ext));

		yNodes[i] = accurateAdd(yNodes[i - 1], eext);
	}

	return yNodes;
}

// Implicit Euler
// y' = x^2 + y^2
// check statment _step and etc!!!
function implicitEuler(_y0, _x_nodes, _step) {
	var yNodes = [_y0],
		denominator = accurateMulti(2, _step),
		c, d;

	for (var i = 1; i < _x_nodes.length; i++) {
		c = accurateAdd(yNodes[i - 1],
						accurateMulti(_step,
									  accurateMulti(_x_nodes[i], _x_nodes[i])));
		d = accurateSub(1, 
						accurateMulti(c, 
									  accurateMulti(4, _step)));

		// console.log("d ", d);
		// console.log("sqrt d ", Math.sqrt(d));
		// console.log("top ", accurateSub(1, Math.sqrt(d)));
		// console.log("bottom ", accurateMulti(2, _step));
		// console.log("full ", accurateDiv(accurateSub(1, Math.sqrt(d)),
		// 						accurateMulti(2, _step)));

		if (d < 0) {
			yNodes[i] = NaN;
		} else {
			yNodes[i] = accurateDiv(accurateSub(1, Math.sqrt(d)),
									denominator);	
		}
	}

	return yNodes;
}

// Imlicit Runge-Kutta2
// y' = x^2 + y^2
// check statment _step and etc!!!
function implicitRungeKutta2(_y0, _x_nodes, _step) {
	var yNodes = [_y0],
		midStep = accurateDiv(_step, 2),
		doubleStep = accurateMulti(2, _step),
		c, d;

	for (var i = 1; i < _x_nodes.length; i++) {
		c = accurateAdd(accurateMulti(midStep, 
									  accurateAdd(accurateAdd(accurateMulti(_x_nodes[i - 1], _x_nodes[i - 1]),
			 			 								   	  accurateMulti(_x_nodes[i], _x_nodes[i])), 
												  accurateMulti(yNodes[i - 1], yNodes[i - 1]))), 
						yNodes[i - 1]);
		d = accurateSub(1, accurateMulti(doubleStep, c));

		if (d < 0) {
			yNodes[i] = NaN;
		} else {
			yNodes[i] = accurateDiv(accurateSub(1, Math.sqrt(d)),
									_step);
		}
	}

	return yNodes;	
}


function buildTable(n, r1, r2, r3, r4, r5, r6, r7, r8)
{
	var result = '';
	for (node in n)
	{
		result += '<tr>';
		result += '<td>'+n[node]+'</td>';
		result += '<td>'+r1[node]+'</td>';
		result += '<td>'+r2[node]+'</td>';
		result += '<td>'+r3[node]+'</td>';
		result += '<td>'+r4[node]+'</td>';
		result += '<td>'+r5[node]+'</td>';
		result += '<td>'+r6[node]+'</td>';
		result += '<td>'+r7[node]+'</td>';
		result += '<td>'+r8[node]+'</td>';
		result += '</tr>';
	}		

	document.getElementById("tbodyResult").innerHTML = result;
}

var y0 = 0,
	xl = 0,
	xr = 1,
	step = 0.1;

// tests
// var y0 = 0,
// 	xl = 0,
// 	xr = 1,
// 	step = 0.1;

// var n = makeNodes(xl, xr, step),
// 	r1 = picard1(y0, n, step),
// 	r2 = picard2(y0, n, step),
// 	r3 = picard3(y0, n, step),
// 	r4 = explicitEuler(derivative, y0, n, step),
// 	r5 = explicitRungeKutta2(derivative, y0, n, step, 0.5),
// 	r6 = explicitRungeKutta2(derivative, y0, n, step, 1),
// 	r7 = implicitEuler(y0, n, step), 
// 	r8 = implicitRungeKutta2(y0, n, step);
	

// console.log("Nodes:", n);
// console.log("Picard1", r6);
// console.log("Picard2", r7);
// console.log("Picard3", r8);
// console.log("Explicit Euler:", r1);
// console.log("Explicit Runge-Kutta2 with alpha 0.5:", r2);
// console.log("Explicit Runge-Kutta2 with alpha 1:", r3);
// console.log("Implicit Euler:", r4);
// console.log("Implicit Runge-Kutta2:", r5);


// buildTable(n, r1, r2, r3, r4, r5, r6, r7, r8);