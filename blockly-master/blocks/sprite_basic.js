'use strict';

goog.require('Blockly.Blocks');
goog.require('Blockly');

Blockly.defineBlocksWithJsonArray([
  {
    'type': 'get_clients',
    'message0': '%{BKY_GET_CLIENTS}',
    'output': 'Array',
    'style': 'math_blocks',
    'inputsInline': true
  },
  {
    'type': 'get_power',
    'message0': '%{BKY_GET_POWER} %1 %{BKY_GET_POWER_2}',
    'args0': [{
      'type': 'input_value',
      'name': 'index',
      'check': 'Number'
    }],
    'output': 'Number',
    'style': 'math_blocks',
    'inputsInline': true
  },
  {
    'type': 'set_blink',
    'message0': '%{BKY_SET_BLINK} %1 %{BKY_SET_BLINK_2}',
    'args0': [{
      'type': 'input_value',
      'name': 'index',
      'check': 'Number',
    }],
    'style': 'math_blocks',
    'inputsInline': true
  },
  {
    'type': 'get_digital',
    'message0': '%{BKY_GET_DIGITAL} %1 %{BKY_GET_DIGITAL_2}',
    'args0': [{
      'type': 'input_value',
      'name': 'index',
      'check': 'Number'
    }],
    'output': 'Number',
    'style': 'math_blocks',
    'inputsInline': true
  },
  {
    'type': 'get_analog',
    'message0': '%{BKY_GET_ANALOG} %1 %{BKY_GET_ANALOG_2}',
    'args0': [{
      'type': 'input_value',
      'name': 'index',
      'check': 'Number'
    }],
    'output': 'Number',
    'style': 'math_blocks',
    'inputsInline': true
  },
  {
    'type': 'set_digital',
    'message0': '%{BKY_SET_DIGITAL} %1 %{BKY_SET_DIGITAL_2} %2',
    'args0': [{
      'type': 'input_value',
      'name': 'index',
      'check': 'Number'
    },
    {
      'type': 'input_value',
      'name': 'value',
      'check': 'Number'
    }],
    'style': 'math_blocks',
    'inputsInline': true
  },
  {
    'type': 'set_analog',
    'message0': '%{BKY_SET_ANALOG} %1 %{BKY_SET_ANALOG_2} %2',
    'args0': [{
      'type': 'input_value',
      'name': 'index',
      'check': 'Number'
    },
    {
      'type': 'field_dropdown',
      'name': 'value',
      'options': [['%{BKY_HIGH}', '1'], ['%{BKY_LOW}', '0']]
    }],
    'style': 'math_blocks',
    'inputsInline': true
  },
  {
    'type': 'set_rainbow',
    'message0': '%{BKY_SET_RAINBOW} %1 %{BKY_SET_RAINBOW_2} %2',
    'args0': [{
      'type': 'input_value',
      'name': 'index',
      'check': 'Number'
    },
    {
      'type': 'input_value',
      'name': 'value',
      'check': 'Colour'
    }],
    'style': 'math_blocks',
    'inputsInline': true
  }
]);
