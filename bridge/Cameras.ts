const fullbowody = require('../build/fullbowody.node');

class Camera {
    #name:string = "";
    #id:number = 0;

    constructor(data:any) {
        this.#name = data.name ?? "Unkwown name";
        this.#id = data.id ?? 0;
    }

    getName() { return this.#name }
    getId() { return this.#id }
}

class CameraManager {
    static GetDevices() {
        return new Promise((resolve, reject) => {
            const res = fullbowody.cameras_getDevices();
            resolve(res);
        });
    }
    
    static GetCameras() {
        return new Promise((resolve, reject) => {
            const res = fullbowody.cameras_getCameras();
            resolve(res);
        });
    }

    static GetCamera(id:number) {
        return new Promise((resolve, reject) => {
            const res = fullbowody.cameras_getCamera(id);
            resolve(res);
        });
    }

    static StartCamera(id:number) {
        return new Promise((resolve, reject) => {
            if (fullbowody.cameras_startCamera(id))
                resolve(undefined);
            else reject( fullbowody.cameras_getLastError(id) );
        });
    }

    static StopCamera(id:number) {
        return new Promise((resolve, reject) => {
            if (fullbowody.cameras_stopCamera(id))
                resolve(undefined);
            else reject( fullbowody.cameras_getLastError(id) );
        });
    }

    static setCameraInput(id:number, input:string|number) {
        return new Promise((resolve, reject) => {
            if (fullbowody.cameras_setCameraInput(id, input))
                resolve(undefined);
            else reject( fullbowody.cameras_getLastError(id) );
        });
    }

    static GetCameraData(id:number) {
        return new Promise((resolve, reject) => {
            const res = fullbowody.cameras_getCameraData(id);
            resolve(res);
        });
    }

    static AddCamera() {
        return new Promise((resolve, reject) => {
            if (fullbowody.cameras_addCamera())
                resolve(undefined);
            else reject( fullbowody.cameras_getLastError(-1) );
        });
    }

    static RemoveCamera(id:number) {
        return new Promise((resolve, reject) => {
            if (fullbowody.cameras_removeCamera(id))
                resolve(undefined);
            else reject( fullbowody.cameras_getLastError(-1) );
        });
    }
}

export default CameraManager;