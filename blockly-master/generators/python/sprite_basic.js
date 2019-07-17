'use strict';

goog.provide('Blockly.Python.sprite_basic');

goog.require('Blockly.Python');

Blockly.Python['get_clients'] = function(block) {
  var code = 'execute_sprite_func("get_clients")';
  return [code, Blockly.Python.ORDER_NONE];
};

Blockly.Python['get_power'] = function(block) {
  var code = 'execute_sprite_func("get_power"' + ', ' +
             Blockly.Python.valueToCode(block, 'index', Blockly.Python.ORDER_ATOMIC) + ')';
  return [code, Blockly.Python.ORDER_NONE];
};

Blockly.Python['set_blink'] = function(block) {
  var code = 'execute_sprite_func("set_blink"' + ', ' + 
             Blockly.Python.valueToCode(block, 'index', Blockly.Python.ORDER_ATOMIC) + ')';
  return code;
};

Blockly.Python['get_digital'] = function(block) {
  var code = 'execute_sprite_func("get_digital"' + ', ' +
             Blockly.Python.valueToCode(block, 'index', Blockly.Python.ORDER_ATOMIC) + ')';
  return [code, Blockly.Python.ORDER_NONE];
};

Blockly.Python['get_analog'] = function(block) {
  var code = 'execute_sprite_func("get_analog"' + ', ' +
             Blockly.Python.valueToCode(block, 'index', Blockly.Python.ORDER_ATOMIC) + ')';
  return [code, Blockly.Python.ORDER_NONE];
};

Blockly.Python['set_digital'] = function(block) {
  var code = 'execute_sprite_func("set_digital"' + ', ' +
             Blockly.Python.valueToCode(block, 'index', Blockly.Python.ORDER_ATOMIC) + ', ' +
             Blockly.Python.valueToCode(block, 'value', Blockly.Python.ORDER_ATOMIC) + ')';
  return code;
};

Blockly.Python['set_analog'] = function(block) {
  var code = 'execute_sprite_func("set_analog"' + ', ' +
             Blockly.Python.valueToCode(block, 'index', Blockly.Python.ORDER_ATOMIC) + ', ' +
             Blockly.Python.valueToCode(block, 'value', Blockly.Python.ORDER_ATOMIC) + ')';
  return code;
};

Blockly.Python['set_rainbow'] = function(block) {
  var code = 'execute_sprite_func("set_rainbow"' + ', ' + 
             Blockly.Python.valueToCode(block, 'index', Blockly.Python.ORDER_ATOMIC) + ', ' +
             Blockly.Python.valueToCode(block, 'value', Blockly.Python.ORDER_ATOMIC) + ')';
  return code;
};
