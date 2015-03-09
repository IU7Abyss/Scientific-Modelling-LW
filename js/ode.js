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

	var div = fixNumber(_number1, _eps) / fixNumber(_number2, _eps);

	return div / Math.pow(10, _eps);
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

// Explicit Euler Method
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