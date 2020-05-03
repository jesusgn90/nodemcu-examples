enum TOPICS {
  SUBSCRIBE = 'NODEMCUDHTHOME01',
}

enum EVENT_TYPES {
  CONNECT = 'connect',
  MESSAGE = 'message',
}

const MQTT_SERVER = 'mqtt://192.168.1.132'

const MQTT_SERVER_CONFIG = { port: 1884 }

export {
  TOPICS,
  EVENT_TYPES,
  MQTT_SERVER,
  MQTT_SERVER_CONFIG,
}
