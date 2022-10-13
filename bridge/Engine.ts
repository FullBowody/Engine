const fullbowody = require('../build/fullbowody.node');

class Engine {
    static start() {
        return new Promise((resolve, reject) => {
            resolve( fullbowody.engine_start() );
        });
    }

    static update(dt:number) {
        return new Promise((resolve, reject) => {
            resolve( fullbowody.engine_update(dt) );
        });
    }

    static stop() {
        return new Promise((resolve, reject) => {
            resolve( fullbowody.engine_stop() );
        });
    }
}

export default Engine;