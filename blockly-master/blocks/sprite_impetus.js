'use strict';

goog.require('Blockly.Blocks');
goog.require('Blockly');

Blockly.defineBlocksWithJsonArray([
  {
    'type': 'set_servo',
    'message0': '%{BKY_SET_SERVO} %1 %{BKY_SET_DIGITAL_2} %2',
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
    'type': 'set_motor_step',
    'message0': '%{BKY_SET_MOTOR_STEP} %1 %{BKY_SET_MOTOR_STEP_2} %2',
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
    'type': 'set_motor_speed',
    'message0': '%{BKY_SET_MOTOR_SPEED} %1 %{BKY_SET_MOTOR_SPEED_2} %2',
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
  }
]);
