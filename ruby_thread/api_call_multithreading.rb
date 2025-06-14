require 'rest-client'
threads = []
mutex = Mutex.new
2.times do
    threads << Thread.new do
        response = RestClient::Request.execute(
            method: :post,
            url: 'localhost:3000/api/v1/questions',
            payload:{
                question: {
                    title: 'New Question-2',
                    tag: 'Ruby'
                }
            }
        )
    end
end

threads.each(&:join)
threads.each do |response|
    puts "#{response.body} #{response.code}"
end