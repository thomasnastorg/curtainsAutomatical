'use strict';
/**
 * @module tplink-smarthome-api
 */
define(function (require, exports, module) {
module.exports = {
  Client: require('./client.js'),
  ResponseError: require('./utils.js').ResponseError
};
});
