require 'socket'

# Create a new TCP server listening on port 3000
server = TCPServer.new(3000)
puts "Server is running on http://localhost:3000"
loop do
  client = server.accept
  request_line = client.gets
  puts "Received request: #{request_line}"
  
  # Simple HTTP response
  response = <<~HEREDOC
    HTTP/1.1 200 OK
    Content-Type: text/html

    <html>
      <body>
        <h1>Hello, World!</h1>
        <p>Your request was: #{request_line}</p>
      </body>
    </html>
  HEREDOC
  client.puts(response)
  client.close
end
