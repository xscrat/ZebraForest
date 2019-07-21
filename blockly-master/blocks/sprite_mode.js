'use strict';

goog.require('Blockly.Blocks');
goog.require('Blockly');

Blockly.defineBlocksWithJsonArray([
  {
    'type': 'set_normal',
    'message0': '%{BKY_SET_NORMAL} %1 %{BKY_SET_NORMAL_2}',
    'args0': [{
      'type': 'input_value',
      'name': 'index',
      'check': 'Number'
    }],
    'style': 'math_blocks',
    'inputsInline': true
  },
  {
    'type': 'set_int',
    'message0': '%{BKY_SET_INT} %1 %{BKY_SET_INT_2} %2',
    'args0': [{
      'type': 'input_value',
      'name': 'index',
      'check': 'Number'
    },
    {
      'type': 'field_dropdown',
      'name': 'value',
      'options': [['%{BKY_RISING}', '0'], ['%{BKY_FALLING}', '1'], ['%{BKY_CHANGE}', '2']]
    }],
    'message1': '%{BKY_CONTROLS_REPEAT_INPUT_DO} %1',
    'args1': [{
      'type': 'input_statement',
      'name': 'DO'
    }],
    "previousStatement": null,
    "nextStatement": null,
    "style": "logic_blocks",
  },
  {
    'type': 'set_lowpower',
    'message0': '%{BKY_SET_LOWPOWER} %1 %{BKY_SET_LOWPOWER_2} %2 %{BKY_SET_LOWPOWER_3} %3',
    'args0': [{
      'type': 'input_value',
      'name': 'index',
      'check': 'Number'
    },
    {
      'type': 'input_value',
      'name': 'interval',
      'check': 'Number'
    },
    {
      'type': 'field_dropdown',
      'name': 'function',
      'options': [['get_digital', 'get_digital'],
                  ['get_analog', 'get_analog'],
                  ['get_power', 'get_power'],
                  ['get_DHT11t', 'get_DHT11t'],
                  ['get_DHT11h', 'get_DHT11h'],
                  ['get_LX', 'get_LX'],
                  ['get_temperature', 'get_temperature'],
                  ['get_pressure', 'get_pressure']]
    }],
    'style': 'math_blocks',
    'inputsInline': true
  },
  {
    'type': 'get_eeprom',
    'message0': '%{BKY_GET_EEPROM} %1 %{BKY_GET_EEPROM_2}',
    'args0': [{
      'type': 'input_value',
      'name': 'index',
      'check': 'Number'
    }],
    'output': 'Number',
    'style': 'math_blocks',
    'inputsInline': true
  }
]);
