'use strict';

goog.provide('Blockly.Constants.ZebraSprite');

goog.require('Blockly.Blocks');
goog.require('Blockly');

Blockly.defineBlocksWithJsonArray([
  {
    "type": "get_clients",
    "message0": "get_clients",
    "output": "Array",
    "style": "math_blocks",
  },
  {
    "type": "get_power",
    "message0": "get_power %1",
    "args0": [{
      "type": "input_value",
      "name": "index",
      "check": "Number"
    }],
    "output": "Number",
    "style": "math_blocks",
  },
  {
    "type": "set_blink",
    "message0": "set_blink %1",
    "args0": [{
      "type": "input_value",
      "name": "index",
      "check": "Number"
    }],
    "output": "Number",
    "style": "math_blocks",
  },
  {
    "type": "get_digital",
    "message0": "get_digital %1",
    "args0": [{
      "type": "input_value",
      "name": "index",
      "check": "Number"
    }],
    "output": "Number",
    "style": "math_blocks",
  },
  {
    "type": "get_analog",
    "message0": "get_analog %1",
    "args0": [{
      "type": "input_value",
      "name": "index",
      "check": "Number"
    }],
    "output": "Number",
    "style": "math_blocks",
  },
  {
    "type": "set_digital",
    "message0": "set_digital %1 %2",
    "args0": [{
      "type": "input_value",
      "name": "index",
      "check": "Number"
    },
    {
      "type": "input_value",
      "name": "value",
      "check": "Number"
    }],
    "output": "Number",
    "style": "math_blocks",
  },
  {
    "type": "set_analog",
    "message0": "set_analog %1 %2",
    "args0": [{
      "type": "input_value",
      "name": "index",
      "check": "Number"
    },
    {
      "type": "input_value",
      "name": "value",
      "check": "Number"
    }],
    "output": "Number",
    "style": "math_blocks",
  },
  {
    "type": "set_rainbow",
    "message0": "set_rainbow %1 %2",
    "args0": [{
      "type": "input_value",
      "name": "index",
      "check": "Number"
    },
    {
      "type": "input_value",
      "name": "value",
      "check": "Colour"
    }],
    "output": "Number",
    "style": "math_blocks",
  },
]);
