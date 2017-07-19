/**
 *  Copyright 2017 Kenny K
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except
 *  in compliance with the License. You may obtain a copy of the License at:
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software distributed under the License is distributed
 *  on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License
 *  for the specific language governing permissions and limitations under the License.
 */
metadata {
	definition (name: "WiFi Contact Sensor", namespace: "r3dey3", author: "Kenny K") {
		capability "Contact Sensor"
		capability "Polling"
		capability "Refresh"
		command "parseResponse"
	}
	simulator {
	}

	tiles (scale: 2){
		multiAttributeTile(name:"contact", type: "", width: 6, height: 4, canChangeIcon: true){
			tileAttribute ("device.contact", key: "PRIMARY_CONTROL") {
				attributeState "open", label:'${name}', action:"", icon:"st.contact.contact.open", backgroundColor: "#e86d13"
				attributeState "closed", label:'${name}', action:"", icon:"st.contact.contact.closed", backgroundColor: "#00a0dc"
			}
		}

		standardTile("refresh", "device.contact", inactiveLabel: false, decoration: "flat", width: 2, height: 2) {
			state "default", label:"", action:"refresh.refresh", icon:"st.secondary.refresh"
		}
	}
	main(["contact"])
	details(["contact", "refresh"])
}

/******************************************************************************
 * Response Parsing
 */
def parse(description) {
	log.trace "parse($description)"
    
	def results = []
    def msg = parseLanMessage(description)
    def json = msg.json
    log.trace "MESSAGE Result: $msg"
    if (msg.status == 200 || msg.header.startsWith('POST')) {
    	log.debug "JSON Result: $json"
        json.each {
        	def n = it.getKey()
        	if (n != "status") {
            	def v = it.getValue()
        		results << createEvent(name: n, value: v)
        	}
        }
    }
  
	results
}
def parseResponse(resp) {
	def json = resp.json
    log.debug "JSON Result: $json"
    json.each {
    	def n = it.key
        if (n != "status") {
            def v = it.value
            sendEvent(name: n, value: v)
        }
    }
}    
/******************************************************************************
 * Refresh interface
 */
def refresh() {
	log.trace "refresh()"
    SUBSCRIBE()
    GET()
}
/******************************************************************************
 * Poll interface
 */
def poll() {
	log.trace "poll()"
	GET()
}

/******************************************************************************
 * Communication functions
 */
private GET() {
    parent.GET(this, "/state.json")
}
private SUBSCRIBE() {
	parent.POST(this, '/subscribe', "http://" + parent.GetCallBackAddress(device.hub) + "/")
}
