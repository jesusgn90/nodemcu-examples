import mqtt from 'mqtt'
import axios from 'axios'
import {
  MQTT_SERVER,
  MQTT_SERVER_CONFIG,
  TOPICS,
  EVENT_TYPES,
} from './helpers'

const TB_TOKEN = 'TB_TOKEN'
const END_POINT = `http://192.168.1.132:8080/api/v1/${TB_TOKEN}/telemetry`

const client  = mqtt.connect(MQTT_SERVER, MQTT_SERVER_CONFIG)

/**
 * Function executed when connected to `MQTT_SERVER`,
 * subscribe to `TOPICS.SUBSCRIBE`.
 */
const connectCallback = (): void => {
  client.subscribe(TOPICS.SUBSCRIBE)
}

/**
 * Function executed when a message arrived any topic that we are
 * subscribed to.
 *
 * Print the topic and the message.
 */
const messageCallback = async (topic: string, message: Buffer): Promise<void> => {
  let parsedJSON = null
  try {
    parsedJSON = JSON.parse(message.toString())
    if (parsedJSON) {
      await axios.post(END_POINT, parsedJSON)
    }
  // eslint-disable-next-line no-empty
  } catch { }
}

// Connect
client.on(EVENT_TYPES.CONNECT, connectCallback)

// Handle incoming messages
client.on(EVENT_TYPES.MESSAGE, messageCallback)
