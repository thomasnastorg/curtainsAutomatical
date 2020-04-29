 /**
 * Configurations of logger.
 */
const winston = require('winston');


const consoleConfig = [
  new winston.transports.Console({
    'colorize': true
  })
];

const createLogger = new winston.Logger({
  'transports': consoleConfig
});

const successLogger = createLogger;
successLogger.add({
  'name': 'access-file',
  'level': 'info',
  'filename': './Log/access.log',
  'json': false,
  'datePattern': 'yyyy-MM-dd-',
  'prepend': true
});

/*const errorLogger = createLogger;
errorLogger.add({
  'name': 'error-file',
  'level': 'error',
  'filename': './Log/error.log',
  'json': false,
  'datePattern': 'yyyy-MM-dd-',
  'prepend': true
});*/

module.exports = {
  'successlog': successLogger,
  //'errorlog': errorLogger
};