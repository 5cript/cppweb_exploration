const extender = require("../../cppdom/module_extensions/extend");

Module['locateFile'] = function(path, prefix) {
	const subPath = './module/';
	return subPath + path;
}

extender(Module);