'use strict';

goog.provide('Blockly.Constants.Sprite');

goog.require('Blockly.Blocks');
goog.require('Blockly');

function getSprteOptionsJson(num) {
  var optionsJson = new Array(num);
  for (var i = 0; i < optionsJson.length; i++) { 
    optionsJson[i] = [(i + 1).toString(), (i + 1).toString()];
  }
  return optionsJson;
}

Blockly.defineBlocksWithJsonArray([
  {
    'type': 'sprite_index',
    'message0': '%1 %2',
    'args0': [{
      'type': 'field_dropdown',
      'name': 'index',
      'options': [['1','1'], ['2', '2']],
    },
    {
      'type': 'input_dummy',
    }],
    'output': 'Number',
  },
]);
