'use strict';

goog.require('Blockly.Blocks');
goog.require('Blockly');

Blockly.defineBlocksWithJsonArray([
  {
    'type': 'get_DHT11t',
    'message0': '%{BKY_GET_DHT11T} %1 %{BKY_GET_DHT11T_2}',
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
    'type': 'get_DHT11h',
    'message0': '%{BKY_GET_DHT11H} %1 %{BKY_GET_DHT11H_2}',
    'args0': [{
      'type': 'input_value',
      'name': 'index',
      'check': 'Number',
    }],
    'output': 'Number',
    'style': 'math_blocks',
    'inputsInline': true
  },
  {
    'type': 'get_LX',
    'message0': '%{BKY_GET_LX} %1 %{BKY_GET_LX_2}',
    'args0': [{
      'type': 'input_value',
      'name': 'index',
      'check': 'Number',
    }],
    'output': 'Number',
    'style': 'math_blocks',
    'inputsInline': true
  },
  {
    'type': 'get_temperature',
    'message0': '%{BKY_GET_TEMPERATURE} %1 %{BKY_GET_TEMPERATURE_2}',
    'args0': [{
      'type': 'input_value',
      'name': 'index',
      'check': 'Number',
    }],
    'output': 'Number',
    'style': 'math_blocks',
    'inputsInline': true
  },
  {
    'type': 'get_pressure',
    'message0': '%{BKY_GET_PRESSURE} %1 %{BKY_GET_PRESSURE_2}',
    'args0': [{
      'type': 'input_value',
      'name': 'index',
      'check': 'Number',
    }],
    'output': 'Number',
    'style': 'math_blocks',
    'inputsInline': true
  },
  {
    'type': 'get_speed',
    'message0': '%{BKY_GET_SPEED} %1 %{BKY_GET_SPEED_2}',
    'args0': [{
      'type': 'input_value',
      'name': 'index',
      'check': 'Number',
    }],
    'output': 'Number',
    'style': 'math_blocks',
    'inputsInline': true
  }
]);
