#!/bin/bash

# Bash script that takes a location as input, 
# then uses an API to gather and echo current weather data.
# The API used is from https://www.weatherapi.com/

location=$1
api_key="" # You will need to get your own API key from weatherapi.com.
api_call="http://api.weatherapi.com/v1/current.json?key=$api_key&q=$location&aqi=no"

curl $api_call --silent >> api_response.json # Save the responce as a JSON.
 
# Using pearl grep to parse weather data. Pearl grep allows the use of \K.
echo "Displaying Current Weather for $(pcre2grep -o '"name":"\K[^"]*' api_response.json):"
echo "It is currently $(pcre2grep -o '"condition":{"text":"\K[^"]*' api_response.json)."
echo "The tempature is $(pcre2grep -o '"temp_f":\K[^,]*' api_response.json)°F. It feels like $(pcre2grep -o '"feelslike_f":\K[^,]*' api_response.json)°F."
echo "The wind is blowing $(pcre2grep -o '"wind_dir":"\K[^"]*' api_response.json), at $(pcre2grep -o '"wind_mph":\K[^,]*' api_response.json)MPH."
echo "The humidity is $(pcre2grep -o '"humidity":\K[^,]*' api_response.json)%."
echo "There is $(pcre2grep -o '"cloud":\K[^,]*' api_response.json)% cloud cover and percipitation is $(pcre2grep -o '"precip_in":\K[^,]*' api_response.json) inches."

rm api_response.json # Delete the JSON responce.