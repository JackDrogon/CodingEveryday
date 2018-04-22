Emitter = require('events')

class MyEmitter extends Emitter {}
const myEmitter = new MyEmitter();
myEmitter.on('event', (a, b) => {
  console.log(a, b, this, this === myEmitter);
})

myEmitter.emit('event', 'a', 'b');
