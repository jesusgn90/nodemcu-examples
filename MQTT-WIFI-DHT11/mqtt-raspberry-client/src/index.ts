import mqtt from 'mqtt'
import {
  MQTT_SERVER,
  MQTT_SERVER_CONFIG,
  TOPICS,
  EVENT_TYPES,
} from './helpers'
import * as Influx from 'influx'

const influx = new Influx.InfluxDB({
  // Replace with InfluxDB database name
  database: 'nodemcu_dht11_01',
  // Replace with InfluxDB sever address
  host: '192.168.1.132',
  // Replace with InfluxDB sever port
  port: 8086,
  // Replace with your InfluxDB login
  username: 'telegraf',
  password: 'secretpassword',
  schema: [
    {
      measurement: TOPICS.SUBSCRIBE,
      fields: {
        temperature: Influx.FieldType.FLOAT,
        humidity: Influx.FieldType.FLOAT,
      },
      tags: [
        TOPICS.SUBSCRIBE,
      ],
    },
  ],
})

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
      await influx.writePoints([
        {
          measurement: TOPICS.SUBSCRIBE,
          tags: { [TOPICS.SUBSCRIBE]: TOPICS.SUBSCRIBE },
          fields: { ...parsedJSON },
        },
      ])
    }
  // eslint-disable-next-line no-empty
  } catch { }
}

// Connect
client.on(EVENT_TYPES.CONNECT, connectCallback)

// Handle incoming messages
client.on(EVENT_TYPES.MESSAGE, messageCallback)
